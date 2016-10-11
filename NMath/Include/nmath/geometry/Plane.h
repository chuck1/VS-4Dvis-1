#ifndef NMATH_GEOMETRY_PLANE
#define NMATH_GEOMETRY_PLANE

#include <nmath/linalg/Vec.h>
#include <nmath/linalg/Mat.h>
//#include <nmath/geometry/Ray.h>

namespace nmath {
	namespace geometry {
		template<unsigned int M>
		class Plane
		{
		public:
			Plane<M>(){}
			Plane<M>(nmath::linalg::Vec<M> nn, float nd) :
				n(nn), d(nd)
			{}

			void	translate(nmath::linalg::Vec<M> t)
			{
				d += nmath::linalg::dot(t, n);
			}
			void rotate(nmath::SMat<M> const & r)
			{
				n = r*n;
			}


		public:
			nmath::linalg::Vec<M> n;
			float d;
		};
	}
}

#endif