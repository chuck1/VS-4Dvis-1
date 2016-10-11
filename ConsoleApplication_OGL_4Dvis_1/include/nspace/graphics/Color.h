#ifndef NSPACE_GRAPHICS_COLOR
#define NSPACE_GRAPHICS_COLOR

#include <nmath/linalg/Vec.h>

namespace nspace {
	namespace graphics {
		class Color: public nmath::linalg::Vec<3>
		{
		public:
			Color operator*(Color const & v)
			{
				Color ret;
				for (int i = 0; i < 3; ++i)
				{
					ret(i) = operator()(i) * v(i);
				}
				return ret;
			}
			Color operator*(float const & f)
			{
				Color ret;
				for (int i = 0; i < 3; ++i)
				{
					ret(i) = operator()(i) * f;
				}
				return ret;
			}
		};
	}
}

#endif