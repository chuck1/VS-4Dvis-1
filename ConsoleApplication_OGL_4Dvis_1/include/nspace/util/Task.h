#ifndef NSPACE_UTIL_TASK
#define NSPACE_UTIL_TASK

namespace nspace
{
	namespace util
	{
		namespace task
		{
			class RayFaceIntersect
			{
			public:
				unsigned int polytope_i;
				unsigned int face_i;
				unsigned int ray_i;
				float k;
				bool intersect;
			};
		}
	}
}

#endif