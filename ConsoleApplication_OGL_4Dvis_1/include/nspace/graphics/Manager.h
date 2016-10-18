#ifndef NSPACE_GRAPHICS_MANAGER
#define NSPACE_GRAPHICS_MANAGER

#include <nspace/decl.h>
#include <nspace/graphics/ocl.h>

namespace nspace {
	namespace graphics {

		class ManagerBase
		{
		public:
			virtual void							reload_buffer() = 0;
			virtual void							render_init() = 0;
			virtual void							render() = 0;

			std::shared_ptr<OCL::Manager>			_M_ocl;

			std::weak_ptr<nspace::app::AppBase>		_M_app;
		};

	}
}

#endif