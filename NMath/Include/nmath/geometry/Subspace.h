#ifndef NMATH_GEOMETRY_SUBSPACE
#define NMATH_GEOMETRY_SUBSPACE

#include <vector>

#include <nmath/util/SerializeVector.h>
#include <nmath/linalg/Mat.h>
#include <nmath/geometry/Inequality.h>

namespace nmath {
	namespace geometry {

		template<unsigned int M, unsigned int K>
		class Subspace
		{
		public:
			nmath::linalg::Vec<K> s(nmath::linalg::Vec<M> x)
			{
				return _M_A.transpose()*(x - _M_p);
			}

			void normalize()
			{
				for (unsigned int j = 0; j < K; ++j)
				{
					float l = 0;
					for (unsigned int i = 0; i < M; ++i)
					{
						l += _M_A(i, j)*_M_A(i, j);
					}
					l = sqrt(l);
					for (unsigned int i = 0; i < M; ++i)
					{
						_M_A(i, j) /= l;
					}
				}
			}

			virtual void serialize(nmath::util::Buffer & c) const
			{
				printf("serialize Subspace\n");

				nmath::util::BlockSizeWriterScoped scoped(c);

				c.write((void*)&_M_A, sizeof(nmath::Mat<M, K>));
				c.write((void*)&_M_p, sizeof(nmath::linalg::Vec<M>));
			}
			virtual void deserialize(nmath::util::Buffer & c)
			{
			}


			/* parameterization */
			nmath::Mat<M, K> _M_A;
			nmath::linalg::Vec<M> _M_p;
		};

		template<unsigned int M, unsigned int K>
		class SubspaceBounded : public Subspace<M, K>
		{
		public:
			using Subspace<M,K>::_M_A;
			using Subspace<M,K>::_M_p;

			virtual void serialize(nmath::util::Buffer & c) const
			{
				nmath::util::BlockSizeWriterScoped scoped(c);

				Subspace<M, K>::serialize(c);
				nmath::util::serialize(c, _M_inequalities);
			}
			virtual void deserialize(nmath::util::Buffer & c)
			{

			}

			/**
			* Add the intersection of this subspace and hyperplane p to the list of inequalities.
			* So add p as a boundary of the subspace.
			*/
			void AddHyperplaneIntersection(nmath::geometry::Plane<M> const & p)
			{
				auto a = _M_A.transpose() * p.n;
				float d = p.d - nmath::linalg::dot(p.n, _M_p);
				_M_inequalities.push_back(Inequality<K>(a, d));
			}

			std::vector<Inequality<K>> _M_inequalities;
		};

	}
}

#endif
