#ifndef NSPACE_LIGHT_LIGHT
#define NSPACE_LIGHT_LIGHT

#include <nmath/linalg/Vec.h>

#include <nspace/graphics/Color.h>

namespace nspace {
	namespace light {

		class Base
		{
		public:
			virtual void serialize(nmath::util::Buffer & c) const = 0;
			virtual void deserialize(nmath::util::Buffer & c) = 0;
		};

		template<unsigned int M>
		class Point: public Base
		{
		public:
			virtual void serialize(nmath::util::Buffer & c) const
			{

			}
			virtual void deserialize(nmath::util::Buffer & c)
			{

			}



			nmath::linalg::Vec<M>	_M_p;
			float _M_atten[3];
			nspace::graphics::Color	_M_color;
		};

	}
}


#endif