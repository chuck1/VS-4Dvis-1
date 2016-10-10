#ifndef NSPACE_APP_APP
#define NSPACE_APP_APP

#include <map>
#include <vector>
#include <memory>

#include <nmath/geometry/Polytope.h>

#include <nspace/decl.h>

#include <nspace/graphics/raycast/Viewport.h>
#include <nspace/light/Light.h>

namespace nspace {
	namespace app {
		class App
		{
		public:
			void init_render();
			void render();
			

			std::shared_ptr<nspace::graphics::raycast::ViewportBase>	_M_viewport;


			typedef nmath::util::ArrayIndirect<std::shared_ptr<nmath::geometry::PolytopeBase>> ARRAY_POLYTOPE;
			typedef std::shared_ptr<ARRAY_POLYTOPE> ARRAY_POLYTOPE_S;

			typedef nmath::util::ArrayIndirect<std::shared_ptr<nspace::light::Base>> ARRAY_LIGHT;
			typedef std::shared_ptr<ARRAY_LIGHT> ARRAY_LIGHT_S;

			ARRAY_POLYTOPE_S											_M_polytopes;
			ARRAY_LIGHT_S												_M_lights;
			
			std::vector< std::shared_ptr<nspace::actor::Base> >			_M_actors;
			
		};
	}
}

#endif