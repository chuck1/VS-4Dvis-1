#ifndef NSPACE_GRAPHICS_RAYCAST_TASK
#define NSPACE_GRAPHICS_RAYCAST_TASK

namespace nspace {
	namespace graphics {
		namespace raycast {
			namespace task {

				template<unsigned int M>
				struct RayFaceIntercept
				{
					unsigned int task_ray_intercept_i;

					unsigned int polytope_i;
					unsigned int face_i;
					
					float k;
					bool intersect;

					// redundent
					unsigned int ray_i;

					unsigned int fail_code;

					// debugging
					float nv;
					float x[M];
					float s[M - 1];
					float A[M*(M - 1)];
				};

				struct RayIntercept
				{
					unsigned int pixel_i;
					unsigned int pixel_j;
					unsigned int ray_i;
					
					float k;
					bool intersect;

					unsigned int _M_task_i;

					//std::vector<RayFaceIntercept> _M_tasks_ray_face_intercept;
					std::vector<unsigned int> _M_tasks_ray_face_intercept_i;
					
				};
				
				
			}
		}
	}
}

#endif