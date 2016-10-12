#ifndef NSPACE_APP_APPTEMPLATE
#define NSPACE_APP_APPTEMPLATE

#include <cstdio>

#include <nspace/app/App.h>
#include <nspace/graphics/raycast/Task.h>

namespace nspace {
	namespace app {
		
		template<unsigned int M>
		class App: public AppBase
		{
		public:

			virtual AppBase::RAY_S make_ray()
			{
				return std::make_shared<nmath::geometry::Ray<M>>();
			}

			
			virtual void create_view_rays()
			{
				_M_rays_view.clear();
				
				unsigned int w = _M_viewport->_M_w;
				unsigned int h = _M_viewport->_M_h;

				float fov = 120;

				float offsetz = 2;

				nmath::linalg::Vec<M> eye;
				//eye(2) = 2.0f * (float)w / (float)h / tan(fov / 2.0f);
				eye(2) = 1.0f * (float)w / (float)h / tan(fov / 2.0f);
				eye(2) += offsetz;

				if (M > 3)
				{
					//eye(3) = 1.f;
				}

				float i0 = ((float)w - 1.0f) / 2.0f;
				float j0 = ((float)h - 1.0f) / 2.0f;
				float dy = 2.0f / (float)h;

				for (unsigned int i = 0; i < w; ++i)
				{
					for (unsigned int j = 0; j < h; ++j)
					{
					
						unsigned int ray_i = i * h + j;

						nmath::geometry::Ray<M> r;

						r.p(0) = ((float)i - i0) * dy;
						r.p(1) = ((float)j - j0) * dy;
						r.p(2) = offsetz;

						r.v = r.p - eye;
						r.v.normalize();

						_M_rays_view.push_back(r);
					}
				}
			}
			virtual void create_tasks_ray_face_intercept()
			{
				_M_tasks_ray_intercept.clear();

				unsigned int w = _M_viewport->_M_w;
				unsigned int h = _M_viewport->_M_h;

				for (unsigned int i = 0; i < w; ++i)
				{
					for (unsigned int j = 0; j < h; ++j)
					{
						unsigned int ray_i = i * h + j;

						nspace::graphics::raycast::task::RayIntercept task_ray_intercept;

						task_ray_intercept.ray_i = ray_i;

						for (unsigned int k = 0; k < _M_polytopes->size(); ++k)
						{
							auto p = std::dynamic_pointer_cast<nmath::geometry::Polytope<M>>(_M_polytopes->operator[](k));

							for (unsigned int l = 0; l < p->_M_faces.size(); ++l)
							{
								nspace::graphics::raycast::task::RayFaceIntercept task;
								
								task.polytope_i = k;
								task.face_i = l;

								task_ray_intercept._M_tasks_ray_face_intercept.push_back(task);
							}
						}

						_M_tasks_ray_intercept.push_back(task_ray_intercept);
					}
				}
			}
			void		do_ray_intercept(
				nspace::graphics::raycast::task::RayIntercept & task)
			{
				for (unsigned int i = 0; i < task._M_tasks_ray_face_intercept.size(); ++i)
				{
					do_ray_face_intercept(task, task._M_tasks_ray_face_intercept[i]);
				}

				task.k = std::numeric_limits<float>::max();
				task.intersect = false;

				for (unsigned int i = 0; i < task._M_tasks_ray_face_intercept.size(); ++i)
				{
					auto & task_ray_face_intercept = task._M_tasks_ray_face_intercept[i];

					if (!task_ray_face_intercept.intersect) continue;

					if (task_ray_face_intercept.k > task.k) continue;
					
					task.k = task_ray_face_intercept.k;
					task.intersect = true;
					task._M_task_i = i;
				}
			}
			void		do_ray_face_intercept(
				nspace::graphics::raycast::task::RayIntercept & task_ray_intercept,
				nspace::graphics::raycast::task::RayFaceIntercept & task)
			{
				//std::cout << "do_ray_face_intercept " << task_ray_intercept.ray_i << std::endl;

				task.intersect = false;
				
				float nv;

				nmath::geometry::Ray<M> & ray = _M_rays_view[task_ray_intercept.ray_i];
				auto p = std::dynamic_pointer_cast<nmath::geometry::Polytope<M>>(_M_polytopes->operator[](task.polytope_i));
				nmath::geometry::Face<M> & f = p->_M_faces[task.face_i];

				float d = nmath::linalg::intersect(nv, ray, f._M_plane);

				if ((nv > 0) || (d < 0)) 
				{
					// no intersection
					return;
				}

				nmath::linalg::Vec<M - 1> s = f.s(ray.x(d));

				if (!f.eval(s)) 
				{
					// no intersection
					return;
				}

				NMATH_DEBUG(20) {
					std::cout << "ray.p   " << ray.p << std::endl;
					std::cout << "ray.v   " << ray.v << std::endl;
					std::cout << "plane.n " << f._M_plane.n << std::endl;
					std::cout << "plane.d " << f._M_plane.d << std::endl;
					std::cout << "f._M_A  " << std::endl;
					std::cout << f._M_A << std::endl;
					std::cout << "s       " << s << std::endl;
				}
				NMATH_DEBUG(10) {
					printf("ray plane intersect at dist=%f\n", d);
				}

				task.intersect = true;
				task.k = d;
			}

			std::vector<nspace::graphics::raycast::task::RayIntercept>		_M_tasks_ray_intercept;
			std::vector<nmath::geometry::Ray<M>>							_M_rays_view;

			virtual void render_init()
			{
				create_view_rays();
				create_tasks_ray_face_intercept();
			}
			virtual void render()
			{
				//printf("App::render\n");

				std::cout << "_M_tasks_ray_intercept " << _M_tasks_ray_intercept.size() << std::endl;

				for (unsigned int i = 0; i < _M_tasks_ray_intercept.size(); ++i)
				{
					nspace::graphics::raycast::task::RayIntercept & task = _M_tasks_ray_intercept[i];
					do_ray_intercept(task);
				}

				unsigned int w = _M_viewport->_M_w;
				unsigned int h = _M_viewport->_M_h;
				
				unsigned char * pixelData = new unsigned char[h * w * 3];
				
				for (unsigned int j = 0; j < h; ++j)
				{
					for (unsigned int i = 0; i < w; ++i)
					{
					
						NMATH_DEBUG(10)printf("pixel %u %u\n", i, j);

						unsigned int ray_i = i * h + j;
						unsigned int pixel_i = j * w * 3 + i * 3;
						pixelData[pixel_i + 0] = 0;
						pixelData[pixel_i + 1] = 0;
						pixelData[pixel_i + 2] = 0;

						nmath::geometry::Ray<M> & r = _M_rays_view[ray_i];

						nspace::graphics::raycast::task::RayIntercept & task = _M_tasks_ray_intercept[ray_i];
						
						bool b = false;
						nmath::linalg::Vec<M> N;
						float dist = std::numeric_limits<float>::max();
						unsigned int polytope_i;
						unsigned int face_i;

#if 0
						{
							for (unsigned int k = 0; k < _M_polytopes->size(); ++k)
							{
								auto p = std::dynamic_pointer_cast<nmath::geometry::Polytope<M>>(_M_polytopes->operator[](k));

								assert(p);

								b = p->intersect(dist, face_i, N, r);

								if (!b) {
									NMATH_DEBUG(10) printf("no intersect with polytope %u\n", k);
									continue;
								}

								polytope_i = k;
							}

						}

						if (!b) {
							NMATH_DEBUG(10) printf("no intersections\n");
							continue; // no intersections, leave pixel black
						}
#else
						if (!task.intersect) {
							NMATH_DEBUG(10) printf("no intersections\n");
							continue; // no intersections, leave pixel black
						}

						polytope_i = task._M_tasks_ray_face_intercept[task._M_task_i].polytope_i;
						face_i = task._M_tasks_ray_face_intercept[task._M_task_i].face_i;
						auto polytope = std::dynamic_pointer_cast<nmath::geometry::Polytope<M>>(_M_polytopes->operator[](polytope_i));
						nmath::geometry::Face<M> & f = polytope->_M_faces[face_i];
						N = f._M_plane.n;
						b = task.intersect;
						dist = task.k;
						
#endif

						NMATH_DEBUG(10) printf("intersection with polytope %i, face %i, dist = %f\n", polytope_i, face_i, dist);

						// calc color

						nspace::graphics::Color color;
						nspace::graphics::Color colorMaterial;
						colorMaterial(1) = 1;
						colorMaterial(2) = 1;

						nmath::linalg::Vec<M> V = -r.v;
						nmath::linalg::Vec<M> p = r.x(dist);

						for (unsigned int k = 0; k < _M_lights->size(); ++k)
						{
							

							std::shared_ptr<nspace::light::Point<M>> l = std::dynamic_pointer_cast<nspace::light::Point<M>>(_M_lights->operator[](k));

							if (!l) continue;

							//printf("light %u\n", k);

							nmath::linalg::Vec<M> L = l->_M_p - p;

							// diffuse

							float a = nmath::linalg::dot(L, N);

							NMATH_DEBUG(10){
								std::cout << "p=" << p << std::endl;
								std::cout << "L=" << L << std::endl;
								std::cout << "N=" << N << std::endl;
								printf("a = %f\n", a);
							}

							if (a > 0)
							{
								float L_len = L.length();
								float atten = l->_M_atten[0] + l->_M_atten[1] * L_len + l->_M_atten[1] * L_len * L_len;
								nspace::graphics::Color colorDiffuse = colorMaterial * l->_M_color * (a / atten);

								NMATH_DEBUG(10)std::cout << "colorDiffuse = " << colorDiffuse << std::endl;

								color += colorDiffuse;
							}
						}

						pixelData[pixel_i + 0] = (unsigned int)(color(0)*255.f);
						pixelData[pixel_i + 1] = (unsigned int)(color(1)*255.f);
						pixelData[pixel_i + 2] = (unsigned int)(color(2)*255.f);

						NMATH_DEBUG(10)std::cout << "pixel color = " << color << std::endl;
						NMATH_DEBUG(10)printf("pixel color = %i %i %i\n", pixelData[pixel_i + 0], pixelData[pixel_i + 1], pixelData[pixel_i + 2]);
					}
				}

				
				
				GLuint textureID;
				glGenTextures(1, &textureID);
				glBindTexture(GL_TEXTURE_2D, textureID);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, pixelData);
				
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

				// render rectangle to display texture on


			}
		};

	}
}

#endif


