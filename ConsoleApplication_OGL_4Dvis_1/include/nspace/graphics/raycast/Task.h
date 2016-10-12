#ifndef NSPACE_GRAPHICS_RAYCAST_TASK
#define NSPACE_GRAPHICS_RAYCAST_TASK

namespace nspace {
	namespace graphics {
		namespace raycast {
			namespace task {

				struct RayFaceIntercept
				{
					unsigned int polytope_i;
					unsigned int face_i;
					
					float k;
					bool intersect;
				};

				struct RayIntercept
				{
					unsigned int ray_i;
					
					float k;
					bool intersect;

					unsigned int _M_task_i;

					std::vector<RayFaceIntercept> _M_tasks_ray_face_intercept;
					
				};
				
				
			}
		}
	}
}

#endif