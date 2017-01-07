#ifndef NSPACE_GRAPHICS_RAYCAST_VIEWPORT
#define NSPACE_GRAPHICS_RAYCAST_VIEWPORT

#include <cmath>
#include <vector>

#include <nmath/geometry/Ray.h>

namespace nspace {
	namespace graphics {
		namespace raycast {

			class ViewportBase
			{
			public:
				int _M_w;
				int _M_h;
			};

			template<int M>
			class Viewport: public ViewportBase
			{
			public:
				void constructRays(int w, int h, double fov)
				{
					_M_w = w;
					_M_h = h;

					double i0 = ((double)w - 1.0) / 2.0;
					double j0 = ((double)h - 1.0) / 2.0;

					double dy = 2.0 / (double)h;

					_M_eye(2) = 2.0 * (double)w / (double)h / tan(fov / 2.0);

					for (int i = 0; i < w; ++i)
					{
						for (int j = 0; j < h; ++j)
						{
							nmath::geometry::Ray<M> r;
							
							r.p(0) = ((double)i - i0) * dy;
							r.p(1) = ((double)j - j0) * dy;

							r.v = r.p - _M_eye;
							r.v.normalize();

							_M_rays.push_back(r);
						}
					}
				}

				std::vector<nmath::geometry::Ray<M>> _M_rays;

				nmath::linalg::Vec<M> _M_eye;

			};

		}
	}
}

#endif