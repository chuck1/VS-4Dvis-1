#ifndef NMATH_GEOMETRY_PLANE
#define NMATH_GEOMETRY_PLANE

#include <nmath/linalg/Vec.h>

namespace nmath {
	namespace geometry {
		template<unsigned int M>
		class Plane
		{
		public:
			Plane<M>(){}
			Plane<M>(nmath::linalg::Vec<M> nn, double nd) :
				n(nn), d(nd)
			{}

			void	translate(nmath::linalg::Vec<M> t)
			{
				d += nmath::linalg::dot(t, n);
			}

		public:
			nmath::linalg::Vec<M> n;
			double d;
		};
	}
}

#endif