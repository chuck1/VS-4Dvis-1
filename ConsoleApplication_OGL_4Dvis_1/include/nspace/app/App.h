#ifndef NSPACE_APP_APP
#define NSPACE_APP_APP

#include <map>
#include <vector>
#include <memory>

#include <nspace/decl.h>

#include <nspace/graphics/raycast/Viewport.h>

namespace nspace {
	namespace app {
		class App
		{
		public:
			void render();

			std::shared_ptr<nspace::graphics::raycast::ViewportBase> _M_viewport;

			std::vector< std::shared_ptr<nspace::actor::Base> >		_M_actors;
		};
	}
}

#endif