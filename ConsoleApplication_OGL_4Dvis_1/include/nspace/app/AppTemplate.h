#ifndef NSPACE_APP_APPTEMPLATE
#define NSPACE_APP_APPTEMPLATE

#include <cstdio>

#include <nspace/app/App.h>

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


			virtual void render()
			{
				printf("App::render");

				unsigned int w = _M_viewport->_M_w;
				unsigned int h = _M_viewport->_M_h;
				
				unsigned char * pixelData = new unsigned char[h * w * 3];
				
				float i0 = ((float)w - 1.0f) / 2.0f;
				float j0 = ((float)h - 1.0f) / 2.0f;
				float dy = 2.0f / (float)h;

				float fov = 120;

				float offsetz = 2;

				nmath::linalg::Vec<M> eye;
				//eye(2) = 2.0f * (float)w / (float)h / tan(fov / 2.0f);
				eye(2) = 1.0f * (float)w / (float)h / tan(fov / 2.0f);
				eye(2) += offsetz;

				for (unsigned int i = 0; i < w; ++i)
				{
					for (unsigned int j = 0; j < h; ++j)
					{
						printf("pixel %u %u\n", i, j);

						unsigned int pixel_i = j * w * 3 + i * 3;
						pixelData[pixel_i + 0] = 0;
						pixelData[pixel_i + 1] = 0;
						pixelData[pixel_i + 2] = 0;

						nmath::geometry::Ray<M> r;

						r.p(0) = ((float)i - i0) * dy;
						r.p(1) = ((float)j - j0) * dy;
						r.p(2) = offsetz;

						r.v = r.p - eye;
						r.v.normalize();

						bool b = false;
						nmath::linalg::Vec<M> N;
						float dist = std::numeric_limits<float>::max();
						unsigned int polytope_i;
						unsigned int face_i;

						for (unsigned int k = 0; k < _M_polytopes->size(); ++k)
						{
							auto p = std::dynamic_pointer_cast<nmath::geometry::Polytope<M>>(_M_polytopes->operator[](k));

							assert(p);

							b = p->intersect(dist, face_i, N, r);

							if (!b) {
								//printf("no intersect with polytope %u\n", k);
								continue; 
							}

							polytope_i = k;
						}

						if (!b) continue; // no intersections, leave pixel black
						
						//printf("intersection with polytope %i, dist = %f\n", polytope_i, dist);

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

							if (false){
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

								//std::cout << "colorDiffuse = " << colorDiffuse << std::endl;

								color += colorDiffuse;
							}
						}

						//std::cout << "pixel color = " << color << std::endl;

						pixelData[pixel_i + 0] = (unsigned int)(color(0)*255.f);
						pixelData[pixel_i + 1] = (unsigned int)(color(1)*255.f);
						pixelData[pixel_i + 2] = (unsigned int)(color(2)*255.f);

						printf("pixel color = %i %i %i\n", pixelData[pixel_i + 0], pixelData[pixel_i + 1], pixelData[pixel_i + 2]);
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