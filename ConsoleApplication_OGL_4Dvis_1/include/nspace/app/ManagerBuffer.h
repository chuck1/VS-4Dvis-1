#ifndef NSPACE_APP_MANAGERBUFFER
#define NSPACE_APP_MANAGERBUFFER

#include <nmath/util/Array.h>
#include <nmath/geometry/Ray.h>

namespace nspace {
	namespace app {
		class ManagerBufferBase
		{

		};

		template<unsigned int M>
		class ManagerBuffer: public ManagerBufferBase
		{
		public:


			nmath::util::Array<nmath::geometry::Ray<M>> _M_rays;
		};
	}
}

#endif


