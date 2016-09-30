#ifndef NMATH_GEOMETRY_PLANE
#define NMATH_GEOMETRY_PLANE

#include <nmath/linalg/Vec.h>

namespace nmath {
	namespace geometry {
		template<unsigned int M>
		class Plane
		{
		public:
			nmath::linalg::Vec<M> n;
			double d;
		};
	}
}

#endif