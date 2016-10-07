#ifndef NMATH_GEOMETRY_SUBSPACE
#define NMATH_GEOMETRY_SUBSPACE

#include <vector>

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

			/* parameterization */
			nmath::Mat<M, K> _M_A;
			nmath::linalg::Vec<M> _M_p;
		};

		template<unsigned int M, unsigned int K>
		class SubspaceBounded : public Subspace<M, K>
		{
		public:
			/**
			* Add the intersection of this subspace and hyperplane p to the list of inequalities.
			* So add p as a boundary of the subspace.
			*/
			void AddHyperplaneIntersection(nmath::geometry::Plane<M> const & p)
			{
				auto a = _M_A.transpose() * p.n;
				double d = p.d - nmath::linalg::dot(p.n, _M_p);
				_M_inequalities.push_back(Inequality<K>(a, d));
			}

			std::vector<Inequality<K>> _M_inequalities;
		};

	}
}

#endif