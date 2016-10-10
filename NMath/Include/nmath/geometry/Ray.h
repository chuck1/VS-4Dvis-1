#ifndef NMATH_GEOMETRY_RAY
#define NMATH_GEOMETRY_RAY

#include <nmath/linalg/Vec.h>

namespace nmath {
	namespace geometry {
		template<unsigned int M>
		class Ray
		{
		public:
			nmath::linalg::Vec<M> x(double k)
			{
				return p + v*k;
			}

		public:
			nmath::linalg::Vec<M> p;
			nmath::linalg::Vec<M> v;
		};
	}
}

#endif


