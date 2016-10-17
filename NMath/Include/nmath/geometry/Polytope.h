#ifndef NMATH_GEOMETRY_POLYTOPE
#define NMATH_GEOMETRY_POLYTOPE

#include <memory>

#include <nmath/util/Array.h>
#include <nmath/geometry/GraphTopology.h>
#include <nmath/geometry/Plane.h>
#include <nmath/geometry/Ray.h>
#include <nmath/geometry/Subspace.h>
#include <nmath/util/Serializable.h>
#include <nmath/util/BlockSizeWriterScoped.h>
#include <nmath/linalg/VecFunctions.h>

namespace nmath {
	namespace geometry {

		template<unsigned int M>
		class Face : public SubspaceBounded<M, M - 1>
		{
		public:
			using SubspaceBounded<M, M - 1>::_M_A;
			using SubspaceBounded<M, M - 1>::_M_inequalities;

			void calc_basis()
			{
				nmath::Mat<M, 1> m;
				for (int i = 0; i < M; ++i) m(i, 0) = _M_plane.n(i);

				auto m2 = nmath::SMat<M>::Identity();

				NMATH_DEBUG(40){
					std::cout << "gaussian elimination" << std::endl;
					std::cout << m << std::endl;
					std::cout << m2 << std::endl;
				}

				nmath::gaussianElimination(m, m2);

				NMATH_DEBUG(40){
					std::cout << "result" << std::endl;
					std::cout << m << std::endl;
					std::cout << m2 << std::endl;
				}

				_M_A = nmath::subMat1(m2.transpose(), 0);

				// normalize column vectors of A
				NMATH_DEBUG(40){
					std::cout << "_M_A" << std::endl;
					std::cout << _M_A << std::endl;
				}

				normalize();

				//std::cout << _M_A << std::endl;
				//getchar(); exit(0);

			}
			bool intersection(nmath::geometry::Ray<M> ray, double & k)
			{
				double k1 = (_M_plane.d - nmath::linalg::dot(_M_plane.n, ray.p)) / nmath::linalg::dot(_M_plane.n, ray.v);

				if (k1 > k) return false;

				// test boundaries
				auto x = ray.x(k1);
				auto s1 = s(x);

				k = k1;

				for (unsigned int i = 0; i < _M_inequalities._M_size; ++i)
				{
					if (!_M_inequalities[i].eval(s1)) {

						NMATH_DEBUG(30) {
							printf("inequality failed\n");
							std::cout << _M_inequalities[i]._M_a << std::endl;
							std::cout << _M_inequalities[i]._M_d << std::endl;
							printf("s = \n");
						}

						return false;
					}
				}

				// passed
				
				return true;
			}

			bool eval(nmath::linalg::Vec<M-1> const & s)
			{
				for (unsigned int j = 0; j < _M_inequalities.size(); ++j)
				{
					nmath::geometry::Inequality<M - 1> & ineq = _M_inequalities[j];

					if (!ineq.eval(s)) {

						NMATH_DEBUG(30) {
							printf("inequality failed\n");
							std::cout << "  a = " << ineq._M_a << std::endl;
							std::cout << "  d = " << ineq._M_d << std::endl;
							std::cout << "  s = " << s << std::endl;
						}

						return false;
					}
				}

				return true;
			}

			void rotate(nmath::SMat<M> const & r)
			{
				_M_plane.rotate(r);
			}

			void serialize(nmath::util::Buffer & c) const
			{
				//printf("serialize Face\n");

				nmath::util::BlockSizeWriterScoped scoped(c);

				SubspaceBounded<M, M - 1>::serialize(c);
				c.write((void*)&_M_plane, sizeof(nmath::geometry::Plane<M>));
			}
			void deserialize(nmath::util::Buffer & c)
			{

			}

		public:
			nmath::geometry::Plane<M> _M_plane;
		};

		class PolytopeBase
		{
		public:
			virtual unsigned int	faces_len() = 0;

			virtual void serialize(nmath::util::Buffer & c) const = 0;
			virtual void deserialize(nmath::util::Buffer & c) = 0;
		};

		template<unsigned int M>
		class Polytope: public FeatureSet<M, M-1>, public PolytopeBase
		{
		public:
			virtual void serialize(nmath::util::Buffer & c) const
			{
				// faces
				//printf("serialize Polytope\n");

				nmath::util::serialize(c, _M_faces);

				//// placeholder to write byte-size of vector block
				//
				//unsigned int d = c.pointer();
				//
				//c += sizeof(unsigned int);

				//unsigned int s = _M_faces.size();

				//c.write(&s, sizeof(unsigned int));
				//
				//for (auto it = _M_faces.begin(); it != _M_faces.end(); ++it)
				//{
				//	// placeholder
				//	unsigned int c1 = c.pointer();
				//	c += sizeof(unsigned int);

				//	(*it).serialize(c);

				//	unsigned int s1 = c - c1;

				//	c -= s1;
				//	c.write((void*)&s1, sizeof(unsigned int));
				//	c += s1;
				//}

				//unsigned int sb = c - d;

				//c -= sb;
				//c.write(&sb, sizeof(unsigned int));
				//c += sb;
			}
			virtual void deserialize(nmath::util::Buffer & c)
			{

			}
			
			void rotate(nmath::SMat<M> const & r)
			{
				for (unsigned int i = 0; i < _M_faces.size(); ++i)
				{
					Face<M> & f = _M_faces[i];

					f.rotate(r);
				}
			}

			bool intersect(float & dist, unsigned int & face_i, nmath::linalg::Vec<M> & N, nmath::geometry::Ray<M> ray)
			{
				NMATH_DEBUG(20) printf("Polytope::intersect\n");
				
				bool b = false;

				for (unsigned int i = 0; i < _M_faces.size(); ++i)
				{
					Face<M> & f = _M_faces[i];

					float nv;

					float d = nmath::linalg::intersect(nv, ray, f._M_plane);



					if (nv > 0) continue; // no intersection
					if (d < 0) continue;

					nmath::linalg::Vec<M - 1> s = f.s(ray.x(d));

					if (!f.eval(s)) continue;
					
					NMATH_DEBUG(20) {
						std::cout << "ray.p   " << ray.p << std::endl;
						std::cout << "ray.v   " << ray.v << std::endl;
						std::cout << "plane.n " << f._M_plane.n << std::endl;
						std::cout << "plane.d " << f._M_plane.d << std::endl;
						std::cout << "f._M_A  " << std::endl;
						std::cout << f._M_A << std::endl;
						std::cout << "s       " << s << std::endl;
						printf("ray plane intersect at dist=%f\n", d);
					}

					b = true;
					if (d < dist)
					{
						dist = d;
						face_i = i;
						N = f._M_plane.n;
					}
				}

				return b;
			}

			virtual unsigned int	faces_len()
			{
				return _M_faces.size();
			}

		public:
			std::vector<Face<M>>			_M_faces;
			
			/** graph
			*/
			std::shared_ptr<nmath::geometry::topo::Graph<M>>	_M_topology;
		};
	}
}

#endif


