#ifndef NMATH_GEOMETRY_POLYTOPE
#define NMATH_GEOMETRY_POLYTOPE


#define NMATH_GEOMETRY_POLYTOPE_MAX_PLANES (32)
#define NMATH_GEOMETRY_POLYTOPE_MAX_VORONOI_REGIONS (32)
#define NMATH_GEOMETRY_VORONOIREGION_MAX_PLANES (32)

namespace nmath {
	namespace geometry {

		template<unsigned int M>
		class VoronoiRegion
		{
		public:
			unsigned int		_M_plane_ref_i[NMATH_GEOMETRY_VORONOIREGION_MAX_PLANES];
			char				_M_plane_ref_sign[NMATH_GEOMETRY_VORONOIREGION_MAX_PLANES];
			unsigned int		_M_plane_ref_size;
		};

		template<unsigned int M>
		class PolytopePrimitive
		{
			VoronoiRegion<M>	_M_voronoi_regions[NMATH_GEOMETRY_POLYTOPE_MAX_VORONOI_REGIONS];
			unsigned int		_M_voronoi_regions_size;

			unsigned int		_M_plane_ref[NMATH_GEOMETRY_POLYTOPE_MAX_PLANES];
			unsigned int		_M_plane_ref_size;
		};

		template<unsigned int M>
		class Polytope: public PolytopePrimitive<M>
		{
		public:
			
		};
	}
}

#endif


