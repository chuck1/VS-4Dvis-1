#ifndef NMATH_GEOMETRY_PLANE
#define NMATH_GEOMETRY_PLANE

#include <nmath/linalg/Vec.h>
<<<<<<< HEAD
=======
#include <nmath/linalg/Mat.h>
//#include <nmath/geometry/Ray.h>
>>>>>>> 268bf01e8f6c31479771525ac3872ff9050934a7

namespace nmath {
	namespace geometry {
		template<unsigned int M>
		class Plane
		{
		public:
<<<<<<< HEAD
			nmath::linalg::Vec<M> n;
			double d;
=======
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
>>>>>>> 268bf01e8f6c31479771525ac3872ff9050934a7
		};
	}
}

#endif