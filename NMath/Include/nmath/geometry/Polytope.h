#ifndef NMATH_GEOMETRY_POLYTOPE
#define NMATH_GEOMETRY_POLYTOPE

#include <memory>

#include <nmath/util/Array.h>
#include <nmath/geometry/GraphTopology.h>
#include <nmath/geometry/Plane.h>
#include <nmath/geometry/Ray.h>
#include <nmath/geometry/Subspace.h>
#include <nmath/util/Serializable.h>


namespace nmath {
	namespace geometry {

		template<unsigned int M>
		class Face : public SubspaceBounded<M, M - 1>
		{
		public:

			template<typename BUFFER>
			void serialize(BUFFER & c) const
			{

			}
			template<typename BUFFER>
			void deserialize(BUFFER & c)
			{

			}

			void calc_basis()
			{
				nmath::Mat<M, 1> m;
				for (int i = 0; i < M; ++i) m(i, 0) = _M_plane.n(i);

				auto m2 = nmath::SMat<M>::Identity();

				nmath::gaussianElimination(m, m2);

				_M_A = nmath::subMat1(m2.transpose(), 0);
			}
			bool intersection(nmath::geometry::Ray<M> ray, double & k)
			{
				double k1 = (_M_plane.d - nmath::linalg::dot(_M_plane.n, ray.p)) / nmath::linalg::dot(_M_plane.n, ray.v);

				if (k1 > k) return false;

				// test boundaries
				auto x = ray.x(k1);
				auto s1 = s(x);

				for (unsigned int i = 0; i < _M_inequalities._M_size; ++i)
				{
					if (!_M_inequalities[i].eval(s1)) return false;;
				}

				// passed
				k = k1;
				return true;
			}
		public:
			nmath::geometry::Plane<M> _M_plane;
		};

		class PolytopeBase
		{};

		template<unsigned int M>
		class Polytope: public FeatureSet<M, M-1>, public PolytopeBase
		{
		public:
			template<typename BUFFER>
			void serialize(BUFFER & c) const
			{
				// faces

				// placeholder to write byte-size of vector block
				BUFFER d = c; c += sizeof(unsigned int);

				unsigned int s = _M_faces.size();
				nmath::util::write(c, &s);
				
				for (auto it = _M_faces.begin(); it != _M_faces.end(); ++it)
				{
					(*it).serialize(c);
				}

				unsigned int sb = c - d;

				nmath::util::write(d, &sb);
			}
			template<typename BUFFER>
			void deserialize(BUFFER & c)
			{

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


