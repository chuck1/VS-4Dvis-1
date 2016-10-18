#ifndef NSPACE_GRAPHICS_PATHTRACE_MANAGER
#define NSPACE_GRAPHICS_PATHTRACE_MANAGER

#include <iostream>
#include <cstdio>
#include <nmath/util/Util.h>
#include <nmath/linalg/VecFunctions.h>
#include <nspace/app/App.h>
#include <nspace/graphics/raycast/Task.h>
#include <nspace/graphics/OCL.h>

namespace nspace {
	namespace graphics {
		namespace pathtrace
		{
			struct Color_1_1_1
			{
				unsigned char c[3];
			};

			struct KernelHeader
			{
				unsigned int h;
				unsigned int w;
				unsigned int s;
				unsigned int counter;
			};

			template<unsigned int M>
			class Manager : public nspace::graphics::ManagerBase
			{
			public:

				typedef nmath::util::ArrayIndirect<nspace::graphics::raycast::task::RayInterceptIn> ARRAY_RAYINTERCEPTIN;
				typedef std::shared_ptr<ARRAY_RAYINTERCEPTIN> ARRAY_RAYINTERCEPTIN_S;


				Manager() : _M_n_ray_samples(2)
				{}

				virtual void							reload_buffer()
				{
					auto app = _M_app.lock();
					_M_memobj_polytopes->EnqueueWrite(app->_M_polytopes->_M_buffer, app->_M_polytopes->buffer_size);
				}
				void									test_index()
				{
					int w = 4;
					int h = 3;
					int s = 2;

					printf("i j k i2 j2 k2\n");

					for (int j = 0; j < h; ++j)
					{
						for (int i = 0; i < w; ++i)
						{	
							for (int k = 0; k < s; ++k)
							{
								int ind = j * w * s + i * s + k;
								
								int k2 = ind % s;

								int i2 = ((ind - k2) / s) % w;

								int j2 = (((ind - k2) / s) - i2) / h;

								printf("%i %i %i   %i %i %i\n", i, j, k, i2, j2, k2);
								

								assert(i == i2);
								assert(j == j2);
								assert(k == k2);
							}
						}
					}

					
					for (int j = 0; j < h; ++j)
					{
						for (int i = 0; i < w; ++i)
						{
								int ind = j * w + i ;

								int i2 = ind % w;

								int j2 = (ind - i2) / w;

								printf("%i %i   %i %i \n", i, j, i2, j2);

								
								assert(i == i2);
								assert(j == j2);
						}
					}

				}
				virtual void							render_init()
				{
					printf("app render init\n");


					nmath::geometry::Ray<M> ray;
					printf("%i\n", sizeof(nmath::geometry::Ray<M>));
					printf("ray.p     %i\n", ((char*)&ray.p - (char*)&ray));
					printf("ray.v     %i\n", ((char*)&ray.v - (char*)&ray));
					printf("ray.color %i\n", ((char*)&ray.color - (char*)&ray));

					//test_index();

					auto app = _M_app.lock();

					unsigned int w = app->_M_viewport->_M_w;
					unsigned int h = app->_M_viewport->_M_h;

					KernelHeader header;
					header.h = h;
					header.w = w;
					header.s = _M_n_ray_samples;
					header.counter = 0;

					// ocl

					printf("openCL init\n");

					_M_ocl = std::make_shared<OCL::Manager>();
					_M_ocl->init();

					char s[64];
					sprintf_s(s, "-D N=(%u)", M);
					auto program = _M_ocl->create_program("kernel/hello.cl", s);

					_M_kernel_path_trace_1 = program->create_kernel("path_trace1");
					_M_kernel_path_trace_2 = program->create_kernel("path_trace2");
					_M_kernel_path_trace_3 = program->create_kernel("path_trace3");

					// polytopes memobj
					_M_memobj_polytopes = _M_ocl->create_buffer(CL_MEM_READ_WRITE, app->_M_polytopes->buffer_size);
					_M_memobj_polytopes->EnqueueWrite(app->_M_polytopes->_M_buffer, app->_M_polytopes->buffer_size);

					// rays memobj
					//sz = _M_rays_view.size() * sizeof(nmath::geometry::Ray<M>);
					_M_memobj_rays = _M_ocl->create_buffer(CL_MEM_READ_WRITE, h*w*_M_n_ray_samples*sizeof(nmath::geometry::Ray<M>));
					
					// pixels
					_M_pixelData = new Color_1_1_1[h * w];
					_M_memobj_pixels = _M_ocl->create_buffer(CL_MEM_READ_WRITE, h*w*sizeof(Color_1_1_1));
					
					auto memobj_header = _M_ocl->create_buffer(CL_MEM_READ_WRITE, sizeof(KernelHeader));
					memobj_header->EnqueueWrite(&header, sizeof(KernelHeader));

					unsigned int counter = 0;
					_M_memobj_counter = _M_ocl->create_buffer(CL_MEM_READ_WRITE, sizeof(unsigned int));
					_M_memobj_counter->EnqueueWrite(&counter, sizeof(unsigned int));





					// kernel args
					int arg = 0;
					_M_kernel_path_trace_1->set_arg(_M_memobj_polytopes, arg++);
					_M_kernel_path_trace_1->set_arg(_M_memobj_rays, arg++);
					_M_kernel_path_trace_1->set_arg(_M_memobj_pixels, arg++);
					_M_kernel_path_trace_1->set_arg(memobj_header, arg++);
					_M_kernel_path_trace_1->set_arg(_M_memobj_counter, arg++);

					arg = 0;
					_M_kernel_path_trace_2->set_arg(_M_memobj_polytopes, arg++);
					_M_kernel_path_trace_2->set_arg(_M_memobj_rays, arg++);
					_M_kernel_path_trace_2->set_arg(_M_memobj_pixels, arg++);
					_M_kernel_path_trace_2->set_arg(memobj_header, arg++);
					_M_kernel_path_trace_2->set_arg(_M_memobj_counter, arg++);

					arg = 0;
					_M_kernel_path_trace_3->set_arg(_M_memobj_polytopes, arg++);
					_M_kernel_path_trace_3->set_arg(_M_memobj_rays, arg++);
					_M_kernel_path_trace_3->set_arg(_M_memobj_pixels, arg++);
					_M_kernel_path_trace_3->set_arg(memobj_header, arg++);
					_M_kernel_path_trace_3->set_arg(_M_memobj_counter, arg++);

					printf("render init finished\n");
					getchar();
				}
				
				virtual void							render()
				{
					//==================================================
					

					auto app = _M_app.lock();

					//==================================================

					unsigned int w = app->_M_viewport->_M_w;
					unsigned int h = app->_M_viewport->_M_h;

					//==================================================
					unsigned int counter = 0;

					unsigned int global_size = 1;

					_M_memobj_counter->EnqueueWrite(&counter, sizeof(unsigned int));

					_M_kernel_path_trace_1->enqueue_ND_range_kernel(global_size, global_size);
					read_counter();
					read_rays();
					getchar();

					_M_memobj_counter->EnqueueWrite(&counter, sizeof(unsigned int));
					
					_M_kernel_path_trace_2->enqueue_ND_range_kernel(global_size, global_size);
					read_counter();
					read_rays();
					getchar();

					_M_memobj_counter->EnqueueWrite(&counter, sizeof(unsigned int));

					_M_kernel_path_trace_3->enqueue_ND_range_kernel(global_size, global_size);
					read_counter();
					//==================================================



					_M_memobj_pixels->EnqueueRead(_M_pixelData, h*w*sizeof(Color_1_1_1));




					GLuint textureID;
					glGenTextures(1, &textureID);
					glBindTexture(GL_TEXTURE_2D, textureID);
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, _M_pixelData);

					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

					// render rectangle to display texture on
				}
				void									read_counter()
				{

					unsigned int c;

					_M_memobj_counter->EnqueueRead(&c, sizeof(unsigned int));

					printf("counter = %i\n", c);

				}
				void									read_rays()
				{
					auto app = _M_app.lock();

					unsigned int w = app->_M_viewport->_M_w;
					unsigned int h = app->_M_viewport->_M_h;
					unsigned int s = _M_n_ray_samples;

					int len = w*h*s;

					std::vector<nmath::geometry::Ray<M>> rays;
					rays.resize(len);

					_M_memobj_rays->EnqueueRead(&rays[0], sizeof(nmath::geometry::Ray<M>)*len);

					

					

					for (int i = 0; i < len; ++i)
					{
						nmath::geometry::Ray<M> & ray = rays[i];

						printf("%i\n", i);
						std::cout << "    " << ray.p << std::endl;
						std::cout << "    " << ray.v << std::endl;
						std::cout << "    " << ray.color << std::endl;
					}
				}

				unsigned int							_M_n_ray_samples;

				Color_1_1_1*							_M_pixelData;

				std::shared_ptr<OCL::Kernel>			_M_kernel_path_trace_1;
				std::shared_ptr<OCL::Kernel>			_M_kernel_path_trace_2;
				std::shared_ptr<OCL::Kernel>			_M_kernel_path_trace_3;

				std::shared_ptr<OCL::MemObj>			_M_memobj_polytopes;
				std::shared_ptr<OCL::MemObj>			_M_memobj_rays;
				std::shared_ptr<OCL::MemObj>			_M_memobj_pixels;
				std::shared_ptr<OCL::MemObj>			_M_memobj_counter;
			};
		}
	}
}


#endif