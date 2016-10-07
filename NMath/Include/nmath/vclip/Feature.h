#ifndef NMATH_GEOMETRY_FEATURE
#define NMATH_GEOMETRY_FEATURE

#include <nmath/geometry/VoronoiRegion.h>

namespace nmath {
	namespace geometry {

		template<int M>
		class FeatureBase
		{
		};

		template<int M, int K>
		class Feature : public FeatureBase<M>
		{
		public:
			VoronoiRegion<M>		_M_voronoi_region;
		};

		template<int M, int K>
		class FeatureSet: public FeatureSet<M, K-1>
		{
		public:
			std::vector<std::shared_ptr<Feature<M, K>>>		_M_features;
		};

		template<int M>
		class FeatureSet<M, 0>
		{
		public:
			std::vector<std::shared_ptr<Feature<M, 0>>>		_M_features;
		};
	}
}

#endif

