#ifndef NSPACE_LIGHT_LIGHT
#define NSPACE_LIGHT_LIGHT

#include <nmath/linalg/Vec.h>

#include <nspace/graphics/Color.h>

namespace nspace {
	namespace light {

		class Base
		{

		};

		template<unsigned int M>
		class Point
		{
		public:
			nmath::linalg::Vec<M>	_M_p;
			float _M_atten[3];
			nspace::graphics::Color	_M_color;
		};

	}
}


#endif