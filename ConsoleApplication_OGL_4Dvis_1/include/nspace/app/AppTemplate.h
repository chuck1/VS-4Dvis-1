#ifndef NSPACE_APP_APPTEMPLATE
#define NSPACE_APP_APPTEMPLATE

#include <cstdio>
#include <nmath/util/Util.h>
#include <nspace/app/App.h>
#include <nspace/graphics/raycast/Task.h>
#include <nspace/graphics/OCL.h>

#define APP_RENDER_GPU (1)
#define APP_RENDER_CPU (0)

#define NSPACE_APP_APPTEMPLATE_DEBUG (0)

#define NSPACE_APP_APPTEMPLATE_PROF (1)

namespace nspace {
	namespace app {

		
		template<unsigned int M>
		class App: public AppBase
		{
		public:

			typedef nmath::util::ArrayIndirect<nspace::graphics::raycast::task::RayInterceptIn> ARRAY_RAYINTERCEPTIN;
			typedef std::shared_ptr<ARRAY_RAYINTERCEPTIN> ARRAY_RAYINTERCEPTIN_S;

			//virtual AppBase::RAY_S make_ray()
			/*{
				return std::make_shared<nmath::geometry::Ray<M>>();
			}
			*/
			
			virtual void reload_buffer()
			{
				_M_memobj_polytope->EnqueueWrite(_M_polytopes->_M_buffer, _M_polytopes->buffer_size);
			}
			virtual void create_view_rays()
			{
				printf("create_view_rays\n");

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
				printf("create_tasks_ray_face_intercept\n");

				_M_tasks_ray_intercept_in = std::make_shared<ARRAY_RAYINTERCEPTIN>();
				_M_tasks_ray_intercept_inout.clear();

				unsigned int w = _M_viewport->_M_w;
				unsigned int h = _M_viewport->_M_h;

				for (unsigned int i = 0; i < w; ++i)
				{
					for (unsigned int j = 0; j < h; ++j)
					{
						unsigned int ray_i = i * h + j;

						std::shared_ptr<nspace::graphics::raycast::task::RayInterceptIn> task_ray_intercept_in = std::make_shared<nspace::graphics::raycast::task::RayInterceptIn>();
						nspace::graphics::raycast::task::RayInterceptInOut task_ray_intercept_inout;

						task_ray_intercept_inout.pixel_i = i;
						task_ray_intercept_inout.pixel_j = j;
						task_ray_intercept_inout.ray_i = ray_i;

						for (unsigned int k = 0; k < _M_polytopes->size(); ++k)
						{
							auto p = std::dynamic_pointer_cast<nmath::geometry::Polytope<M>>(_M_polytopes->operator[](k));

							for (unsigned int l = 0; l < p->_M_faces.size(); ++l)
							{
								nspace::graphics::raycast::task::RayFaceIntercept<M> task;
								
								task.polytope_i = k;
								task.face_i = l;
								task.task_ray_intercept_i = ray_i;
								task.ray_i = task_ray_intercept_inout.ray_i;

								task_ray_intercept_in->_M_tasks_ray_face_intercept_i.push_back(_M_tasks_ray_face_intercept.size());
								_M_tasks_ray_face_intercept.push_back(task);
							}
						}

						_M_tasks_ray_intercept_in->push_back(task_ray_intercept_in);
						_M_tasks_ray_intercept_inout.push_back(task_ray_intercept_inout);
					}
				}
			}
			void		do_ray_intercept(
				std::shared_ptr<nspace::graphics::raycast::task::RayInterceptIn> & task_in,
				nspace::graphics::raycast::task::RayInterceptInOut & task_inout)
			{
				/*for (unsigned int i = 0; i < task._M_tasks_ray_face_intercept.size(); ++i)
				{
					do_ray_face_intercept(task, task._M_tasks_ray_face_intercept[i]);
				}*/

				task_inout.k = std::numeric_limits<float>::max();
				task_inout.intersect = false;

				NMATH_DEBUG(10) printf("pixel %i %i ###############################\n", task_inout.pixel_i, task_inout.pixel_j);

				for (unsigned int i = 0; i < task_in->_M_tasks_ray_face_intercept_i.size(); ++i)
				{
					auto & task_ray_face_intercept = _M_tasks_ray_face_intercept[task_in->_M_tasks_ray_face_intercept_i[i]];

					if (!task_ray_face_intercept.intersect) continue;

					if (task_ray_face_intercept.k > task_inout.k) continue;
					
					task_inout.k = task_ray_face_intercept.k;
					task_inout.intersect = true;
					task_inout._M_task_i = i;
				}
			}
			void		do_ray_face_intercept(
				//nspace::graphics::raycast::task::RayIntercept & task_ray_intercept)
				nspace::graphics::raycast::task::RayFaceIntercept<M> & task)
			{
				//std::cout << "do_ray_face_intercept " << task_ray_intercept.ray_i << std::endl;

				

				task.fail_code = 0;
				task.intersect = false;
				
				float nv;

				//nmath::geometry::Ray<M> & ray = _M_rays_view[task_ray_intercept.ray_i];
				nmath::geometry::Ray<M> & ray = _M_rays_view[task.ray_i];

				auto p = std::dynamic_pointer_cast<nmath::geometry::Polytope<M>>(_M_polytopes->operator[](task.polytope_i));
				nmath::geometry::Face<M> & f = p->_M_faces[task.face_i];

				float d = nmath::linalg::intersect(nv, ray, f._M_plane);

				// debugging
				memcpy(&task.A, &f._M_A(0,0), sizeof(nmath::Mat<M,M-1>));

				//debugging
				task.nv = nv;

				if ((nv > 0) || (d < 0)) 
				{
					// no intersection
					return;
				}

				auto x = ray.x(d);

				//debugging
				memcpy(&task.x, &x, sizeof(nmath::linalg::Vec<M>));

				nmath::linalg::Vec<M - 1> s = f.s(x);

				//debugging
				memcpy(&task.s, &s, sizeof(nmath::linalg::Vec<M-1>));

				if (!f.eval(s)) 
				{
					// no intersection

					NMATH_DEBUG(20) {
						printf("ray plane intersect at dist=%f\n", d);
					}
					NMATH_DEBUG(30) {
						std::cout << "  ray.p   " << ray.p << std::endl;
						std::cout << "  ray.v   " << ray.v << std::endl;
						std::cout << "  plane.n " << f._M_plane.n << std::endl;
						std::cout << "  plane.d " << f._M_plane.d << std::endl;
						std::cout << "  f._M_A  " << std::endl;
						std::cout << f._M_A << std::endl;
						std::cout << "  x       " << x << std::endl;
						std::cout << "  s       " << s << std::endl;
					}

					return;
				}

				task.intersect = true;
				task.k = d;
			}

			
			
			

			virtual void						render_init()
			{
				printf("app render init\n");

				create_view_rays();
				create_tasks_ray_face_intercept();

				// ocl

				printf("openCL init\n");

				_M_ocl = std::make_shared<OCL::Manager>();

				_M_ocl->init();

				auto program = _M_ocl->create_program("kernel/hello.cl", "-D N=(4)");

				_M_kernel_ray_face_intercept = program->create_kernel("ray_cast");

				
				unsigned int sz;
				// polytopes memobj
				_M_memobj_polytope = _M_ocl->create_buffer(CL_MEM_READ_WRITE, _M_polytopes->buffer_size);
				_M_memobj_polytope->EnqueueWrite(_M_polytopes->_M_buffer, _M_polytopes->buffer_size);

				// rays memobj
				sz = _M_rays_view.size() * sizeof(nmath::geometry::Ray<M>);
				auto memobj_rays_view = _M_ocl->create_buffer(CL_MEM_READ_WRITE, sz);
				memobj_rays_view->EnqueueWrite(&_M_rays_view[0], sz);

				// tasks memobj
				sz = _M_tasks_ray_face_intercept.size() * sizeof(nspace::graphics::raycast::task::RayFaceIntercept<M>);
				_M_memobj_tasks_ray_face_intercept = _M_ocl->create_buffer(CL_MEM_READ_WRITE, sz);
				_M_memobj_tasks_ray_face_intercept->EnqueueWrite(&_M_tasks_ray_face_intercept[0], sz);

				// tasks len memobj
				unsigned int tasks_len = _M_tasks_ray_face_intercept.size();
				auto memobj_tasks_len = _M_ocl->create_buffer(CL_MEM_READ_WRITE, sizeof(unsigned int));
				memobj_tasks_len->EnqueueWrite(&tasks_len, sizeof(unsigned int));

				// tasks counter
				unsigned int counter = 0;
				_M_memobj_counter = _M_ocl->create_buffer(CL_MEM_READ_WRITE, sizeof(unsigned int));
				_M_memobj_counter->EnqueueWrite(&counter, sizeof(unsigned int));

				// kernel args
				int arg = 0;
				//__global void * polytopes,
				_M_kernel_ray_face_intercept->set_arg(_M_memobj_polytope, arg++);

				//__global void * lights,

				//__global struct Ray * rays,
				_M_kernel_ray_face_intercept->set_arg(memobj_rays_view, arg++);

				//__global struct RayFaceInterceptTask * tasks_ray_face,
				_M_kernel_ray_face_intercept->set_arg(_M_memobj_tasks_ray_face_intercept, arg++);

				//unsigned int tasks_len,
				_M_kernel_ray_face_intercept->set_arg(memobj_tasks_len, arg++);

				//__global char * tasks_ray_in,
				auto memobj_tasks_ray_in = _M_ocl->create_buffer(CL_MEM_READ_WRITE, _M_tasks_ray_intercept_in->buffer_size);
				memobj_tasks_ray_in->EnqueueWrite(_M_tasks_ray_intercept_in->_M_buffer, _M_tasks_ray_intercept_in->buffer_size);
				_M_kernel_ray_face_intercept->set_arg(memobj_tasks_ray_in, arg++);
				printf("tasks_ray_in size %u\n", _M_tasks_ray_intercept_in->size());
				printf("tasks_ray_in bsize %u\n", _M_tasks_ray_intercept_in->buffer_size);

				for (unsigned int i = 0; i < (_M_tasks_ray_intercept_in->buffer_size / sizeof(unsigned int)); ++i)
				{
					printf("  %i\n", ((unsigned int *)_M_tasks_ray_intercept_in->_M_buffer)[i]);
				}

				//__global struct RayInterceptInOut * tasks_ray_inout,
				sz = _M_tasks_ray_intercept_inout.size() * sizeof(nspace::graphics::raycast::task::RayInterceptInOut);
				_M_memobj_tasks_ray_inout = _M_ocl->create_buffer(CL_MEM_READ_WRITE, sz);
				_M_memobj_tasks_ray_inout->EnqueueWrite(&_M_tasks_ray_intercept_inout[0], sz);
				_M_kernel_ray_face_intercept->set_arg(_M_memobj_tasks_ray_inout, arg++);

				//__global uint * tasks_ray_inout_len,
				unsigned int tasks_ray_inout_len = _M_tasks_ray_intercept_inout.size();
				auto memobj_tasks_ray_inout_len = _M_ocl->create_buffer(CL_MEM_READ_WRITE, sizeof(unsigned int));
				memobj_tasks_ray_inout_len->EnqueueWrite(&tasks_ray_inout_len, sizeof(unsigned int));
				_M_kernel_ray_face_intercept->set_arg(memobj_tasks_ray_inout_len, arg++);

				//__global float3 * pixel_color,
				//volatile __global uint * counter
				_M_kernel_ray_face_intercept->set_arg(_M_memobj_counter, arg++);






				// pointer_calc_test
				_M_kernel_pointer_calc_test = program->create_kernel("pointer_calc_test");

				_M_memobj_test_polytope = _M_ocl->create_buffer(CL_MEM_READ_WRITE, _M_polytopes->buffer_size);
				_M_memobj_test_polytope->EnqueueWrite(_M_polytopes->_M_buffer, _M_polytopes->buffer_size);

				

				unsigned int size = sizeof(float) * (M) * 100;
				_M_memobj_test_out_float = _M_ocl->create_buffer(CL_MEM_READ_WRITE, size);

				size = sizeof(unsigned int) * 100;
				_M_memobj_test_out_uint = _M_ocl->create_buffer(CL_MEM_READ_WRITE, size);

				arg = 0;
				_M_kernel_pointer_calc_test->set_arg(_M_memobj_test_polytope, arg++);
				_M_kernel_pointer_calc_test->set_arg(memobj_rays_view, arg++);
				_M_kernel_pointer_calc_test->set_arg(_M_memobj_tasks_ray_face_intercept, arg++);
				_M_kernel_pointer_calc_test->set_arg(_M_memobj_test_out_uint, arg++);
				_M_kernel_pointer_calc_test->set_arg(_M_memobj_test_out_float, arg++);


				printf("render init finished\n");
				getchar();
			}
			virtual void						render_ray_face_intercept()
			{
				//test_pointer_calc();

				// OCL

				unsigned int size_tasks_ray_face = _M_tasks_ray_face_intercept.size() * sizeof(nspace::graphics::raycast::task::RayFaceIntercept<M>);

				unsigned int work_group_size = 512;

				_M_kernel_ray_face_intercept->enqueue_ND_range_kernel(work_group_size, work_group_size);

				unsigned int counter;
				_M_memobj_counter->EnqueueRead(&counter, sizeof(unsigned int));

#if APP_RENDER_GPU

				// read

				_M_memobj_tasks_ray_face_intercept->EnqueueRead(&_M_tasks_ray_face_intercept[0], size_tasks_ray_face);

				//printf("App::render\n");
#else
				_M_tasks_ray_face_intercept_result.resize(_M_tasks_ray_face_intercept.size());
				_M_memobj_tasks_ray_face_intercept->EnqueueRead(&_M_tasks_ray_face_intercept_result[0], size_tasks_ray_face);
#endif

				//=====================================
#if APP_RENDER_CPU
				for (unsigned int i = 0; i < _M_tasks_ray_face_intercept.size(); ++i)
				{
					nspace::graphics::raycast::task::RayFaceIntercept<M> & task = _M_tasks_ray_face_intercept[i];
					//do_ray_face_intercept(_M_tasks_ray_intercept[task.task_ray_intercept_i], task);
					do_ray_face_intercept(task);
				}
#endif
				//==================================================

#if APP_RENDER_DEBUG

				std::cout << "_M_tasks_ray_intercept      " << _M_tasks_ray_intercept.size() << std::endl;
				std::cout << "_M_tasks_ray_face_intercept " << _M_tasks_ray_face_intercept.size() << std::endl;

				unsigned int c1 = 0;
				unsigned int c2 = 0;
				unsigned int c12 = 0;

				for (unsigned int i = 0; i < _M_tasks_ray_face_intercept.size(); ++i)
				{
					auto & t1 = _M_tasks_ray_face_intercept[i];
					auto & t2 = _M_tasks_ray_face_intercept_result[i];

					if (t1.intersect) ++c1;
					if (t2.intersect) ++c2;
					if (t1.intersect && t2.intersect) ++c12;

					if (t1.intersect || t2.intersect)
					{

						printf("%6i\n", i);
						printf("      ray       %16i %16i\n", t1.ray_i, t2.ray_i);
						printf("      polytope  %16i %16i\n", t1.polytope_i, t2.polytope_i);
						printf("      face      %16i %16i\n", t1.face_i, t2.face_i);
						printf("      intersect %16i %16i\n", t1.intersect, t2.intersect);
						printf("      fail code %16i %16i\n", t1.fail_code, t2.fail_code);
						printf("      k         %16.4e %16.4e\n", t1.k, t2.k);
						printf("      nv        %16.4e %16.4e\n", t1.nv, t2.nv);
						for (int j = 0; j < M; ++j)
						{
							printf("      x         %16.4e %16.4e\n", t1.x[j], t2.x[j]);
						}
						for (int j = 0; j < (M - 1); ++j)
						{
							printf("      s         %16.4e %16.4e\n", t1.s[j], t2.s[j]);
						}
						for (int j = 0; j < (M*(M - 1)); ++j)
						{
							printf("      A         %16.4e %16.4e\n", t1.A[j], t2.A[j]);
						}
					}
				}

				printf("sizeof(nmath::Mat<M,M-1>): %i\n", sizeof(nmath::Mat<M, M - 1>));


				printf("c1:   %i\n", c1);
				printf("c2:   %i\n", c2);
				printf("c12:  %i\n", c12);
#endif

#if NSPACE_APP_APPTEMPLATE_DEBUG
				unsigned int c1 = 0;
				unsigned int c2 = 0;
				unsigned int c12 = 0;
				for (unsigned int i = 0; i < _M_tasks_ray_face_intercept.size(); ++i)
				{
					auto & t1 = _M_tasks_ray_face_intercept[i];
					//auto & t2 = _M_tasks_ray_face_intercept_result[i];

					if (t1.intersect) ++c1;
					//if (t2.intersect) ++c2;
					//if (t1.intersect && t2.intersect) ++c12;
				}
				printf("c1:   %i\n", c1);
				printf("c2:   %i\n", c2);
				printf("c12:  %i\n", c12);
				printf("counter: %i\n", counter);

				unsigned int test[4];
				for (int i = 0; i < 4; ++i) test[i] = i + 1;

				//printf("tasks check sum: %8u\n", nmath::util::checksum2<unsigned int>((char*)&test, 4*4));
				//printf("%i\n", size_tasks_ray_face);
				printf("tasks check sum: %8u\n", nmath::util::checksum2<unsigned long>((char*)&_M_tasks_ray_face_intercept[0], size_tasks_ray_face));
#endif
			}
			virtual void						render_ray_view()
			{
//#if APP_RENDER_CPU
				for (unsigned int i = 0; i < _M_tasks_ray_intercept_in->size(); ++i)
				{
					auto & task_in = _M_tasks_ray_intercept_in->operator[](i);
					nspace::graphics::raycast::task::RayInterceptInOut & task_inout = _M_tasks_ray_intercept_inout[i];
					do_ray_intercept(task_in, task_inout);
				}
//#endif
//#if APP_RENDER_GPU
				// read tasks ray view inout

				unsigned int size = _M_tasks_ray_intercept_inout.size() * sizeof(nspace::graphics::raycast::task::RayInterceptInOut);

				std::vector<nspace::graphics::raycast::task::RayInterceptInOut>		tasks_ray_intercept_inout_2;
				tasks_ray_intercept_inout_2.resize(_M_tasks_ray_intercept_inout.size());
				
				//_M_memobj_tasks_ray_inout->EnqueueRead(&_M_tasks_ray_intercept_inout[0], size);
				_M_memobj_tasks_ray_inout->EnqueueRead(&tasks_ray_intercept_inout_2[0], size);



				//debug
				for (unsigned int i = 0; i < _M_tasks_ray_intercept_inout.size(); ++i)
				{
					auto & t1 = _M_tasks_ray_intercept_inout[i];
					auto & t2 = tasks_ray_intercept_inout_2[i];

					printf("pixel_i   %8u %8u\n", t1.pixel_i, t2.pixel_i);
					printf("pixel_j   %8u %8u\n", t1.pixel_j, t2.pixel_j);
					printf("ray_i     %8u %8u\n", t1.ray_i, t2.ray_i);
					printf("k         %8.2e %8.2e\n", t1.k, t2.k);
					printf("intersect %8u %8u\n", t1.intersect, t2.intersect);
					printf("task_i    %8u %8u\n", t1._M_task_i, t2._M_task_i);
					/*
					unsigned int pixel_i;
					unsigned int pixel_j;
					unsigned int ray_i;

					float k;
					bool intersect;

					unsigned int _M_task_i;
					*/
				}

//#endif
			}
			virtual void						render2(unsigned char * pixelData)
			{
				//==================================================

				unsigned int w = _M_viewport->_M_w;
				unsigned int h = _M_viewport->_M_h;

				

				for (unsigned int j = 0; j < h; ++j)
				{
					for (unsigned int i = 0; i < w; ++i)
					{

						NMATH_DEBUG(10)printf("pixel %u %u ====================================\n", i, j);

						unsigned int ray_i = i * h + j;
						unsigned int pixel_i = j * w * 3 + i * 3;
						pixelData[pixel_i + 0] = 0;
						pixelData[pixel_i + 1] = 0;
						pixelData[pixel_i + 2] = 0;

						nmath::geometry::Ray<M> & r = _M_rays_view[ray_i];

						std::shared_ptr<nspace::graphics::raycast::task::RayInterceptIn> & task_in = _M_tasks_ray_intercept_in->operator[](ray_i);
						nspace::graphics::raycast::task::RayInterceptInOut & task_inout = _M_tasks_ray_intercept_inout[ray_i];

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

						if (!task_inout.intersect) {
							NMATH_DEBUG(10) printf("no intersections\n");
							pixelData[pixel_i + 0] = 128;
							continue; // no intersections, leave pixel black
						}

						auto & task_ray_face_intercept_i = task_in->_M_tasks_ray_face_intercept_i[task_inout._M_task_i];
						auto & task_ray_face_intercept = _M_tasks_ray_face_intercept[task_ray_face_intercept_i];

						polytope_i = task_ray_face_intercept.polytope_i;
						face_i = task_ray_face_intercept.face_i;
						auto polytope = std::dynamic_pointer_cast<nmath::geometry::Polytope<M>>(_M_polytopes->operator[](polytope_i));
						nmath::geometry::Face<M> & f = polytope->_M_faces[face_i];
						N = f._M_plane.n;
						b = task_inout.intersect;
						dist = task_inout.k;

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

							NMATH_DEBUG(50){
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

								NMATH_DEBUG(50)std::cout << "colorDiffuse = " << colorDiffuse << std::endl;

								color += colorDiffuse;
							}
						}

						pixelData[pixel_i + 0] = (unsigned int)(color(0)*255.f);
						pixelData[pixel_i + 1] = (unsigned int)(color(1)*255.f);
						pixelData[pixel_i + 2] = (unsigned int)(color(2)*255.f);

						NMATH_DEBUG(50){
							std::cout << "pixel color = " << color << std::endl;
							printf("pixel color = %i %i %i\n", pixelData[pixel_i + 0], pixelData[pixel_i + 1], pixelData[pixel_i + 2]);
						}
					}
				}
			}
			virtual void						render()
			{
				//==================================================
				{
					std::clock_t start;
					if(NSPACE_APP_APPTEMPLATE_PROF) start = std::clock();
					render_ray_face_intercept();
					if (NSPACE_APP_APPTEMPLATE_PROF) printf("render_ray_face_intercept time: %i\n", std::clock() - start);
				}

				{
					std::clock_t start;
					if (NSPACE_APP_APPTEMPLATE_PROF) start = std::clock();
					render_ray_view();
					if (NSPACE_APP_APPTEMPLATE_PROF) printf("render_ray_view time: %i\n", std::clock() - start);
				}
				

				//==================================================

				unsigned int w = _M_viewport->_M_w;
				unsigned int h = _M_viewport->_M_h;

				unsigned char * pixelData = new unsigned char[h * w * 3];

				{
					std::clock_t start;
					if (NSPACE_APP_APPTEMPLATE_PROF) start = std::clock();
					render2(pixelData);
					if (NSPACE_APP_APPTEMPLATE_PROF) printf("render2 time: %i\n", std::clock() - start);
				}

				GLuint textureID;
				glGenTextures(1, &textureID);
				glBindTexture(GL_TEXTURE_2D, textureID);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, pixelData);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

				// render rectangle to display texture on
			}
			void								test_pointer_calc()
			{
				printf("test pointer calc\n");
				
				_M_kernel_pointer_calc_test->enqueue_ND_range_kernel(1, 1);

				unsigned int out_uint[100];
				//nmath::linalg::Vec<M> out_float[100];
				float out_float[100*M];

				_M_memobj_test_out_uint->EnqueueRead(out_uint, sizeof(unsigned int)* 100);
				_M_memobj_test_out_float->EnqueueRead(out_float, sizeof(float)* M * 100);
				
				// print

				nmath::geometry::Ray<M> ray;
				nmath::geometry::Plane<M> plane;

				printf("position of ray p:   %2i\n", (int)((char*)(&ray.p) - (char*)&ray));
				printf("position of ray v:   %2i\n", (int)((char*)(&ray.v) - (char*)&ray));
				printf("position of plane n: %2i\n", (int)((char*)(&plane.n) - (char*)&plane));
				printf("position of plane d: %2i\n", (int)((char*)(&plane.d) - (char*)&plane));
				
				printf("sizeof(Vec<%i>)    = %4i\n", M, sizeof(nmath::linalg::Vec<M>));
				printf("sizeof(Mat<%i,%i>)  = %4i\n", M, M-1, sizeof(nmath::Mat<M,M-1>));
				printf("sizeof(Plane<%i>)  = %4i\n", M, sizeof(nmath::geometry::Plane<M>));
				printf("sizeof(Ray<%i>)    = %4i\n", M, sizeof(nmath::geometry::Ray<M>));

				for (unsigned int i = 0; i < 7; ++i)
				{
					printf("out_uint[%2i] = %8i\n", i, out_uint[i]);
				}

				std::shared_ptr<nmath::geometry::Polytope<M>> polytope = std::dynamic_pointer_cast<nmath::geometry::Polytope<M>>(_M_polytopes->operator[](0));
				auto face = polytope->_M_faces[0];
				










				if (0){
					for (int i = 0; i < face._M_inequalities.size(); ++i)
					{
						printf("%2i %16f %16f\n", i, out_float[i], face._M_inequalities[i]._M_d);
					}
				}
				if (0){
					for (int j = 0; j < 4; ++j)
					{
						printf("\n");
						std::cout << out_float[j] << std::endl;
						std::cout << _M_rays_view[j].p << std::endl;
					}
				}
				if (0)
				{
					printf("face._M_plane.n\n");
					std::cout << out_float[0] << std::endl;
					std::cout << face._M_plane.n << std::endl;

					for (int j = 0; j < 4; ++j)
					{
						printf("\n");
						std::cout << out_float[j + 1] << std::endl;
						std::cout << face._M_inequalities[j]._M_a << std::endl;
					}
				}
				getchar(); exit(0);
			}
			




			ARRAY_RAYINTERCEPTIN_S												_M_tasks_ray_intercept_in;
			std::vector<nspace::graphics::raycast::task::RayInterceptInOut>		_M_tasks_ray_intercept_inout;
			std::vector<nspace::graphics::raycast::task::RayFaceIntercept<M>>	_M_tasks_ray_face_intercept;
			std::vector<nmath::geometry::Ray<M>>								_M_rays_view;

			std::vector<nspace::graphics::raycast::task::RayFaceIntercept<M>>	_M_tasks_ray_face_intercept_result;


			std::shared_ptr<OCL::Manager>		_M_ocl;
			
			std::shared_ptr<OCL::Kernel>		_M_kernel_ray_face_intercept;
			std::shared_ptr<OCL::Kernel>		_M_kernel_pointer_calc_test;

			std::shared_ptr<OCL::MemObj>		_M_memobj_polytope;
			std::shared_ptr<OCL::MemObj>		_M_memobj_tasks_ray_face_intercept;
			std::shared_ptr<OCL::MemObj>		_M_memobj_tasks_ray_inout;
			std::shared_ptr<OCL::MemObj>		_M_memobj_counter;
			std::shared_ptr<OCL::MemObj>		_M_memobj_test_polytope;
			std::shared_ptr<OCL::MemObj>		_M_memobj_test_out_uint;
			std::shared_ptr<OCL::MemObj>		_M_memobj_test_out_float;
		};
	}
}

#endif


