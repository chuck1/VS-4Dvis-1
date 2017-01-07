#ifndef NMATH_GEOMETRY_VORONOIREGION
#define NMATH_GEOMETRY_VORONOIREGION

#include <vector>

#include <nmath/geometry/Plane.h>

namespace nmath {
	namespace geometry {

		template<unsigned int M>
		class VoronoiRegionBoundary
		{
		public:
			nmath::geometry::Plane<M>	_M_plane;
		};

		template<unsigned int M>
		class VoronoiRegion
		{
		public:
			std::vector<VoronoiRegionBoundary<M>>		_M_boundaries;
		};

	}
}

#endif