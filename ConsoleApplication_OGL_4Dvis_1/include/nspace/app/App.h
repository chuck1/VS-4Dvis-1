#ifndef NSPACE_APP_APP
#define NSPACE_APP_APP

#include <map>
#include <vector>
#include <memory>

#include <nmath/geometry/Polytope.h>

#include <nspace/decl.h>

#include <nspace/graphics/raycast/Viewport.h>
#include <nspace/graphics/Manager.h>
#include <nspace/light/Light.h>


namespace nspace {
	namespace app {
		class AppBase
		{
		public:
			
			//typedef std::shared_ptr<nmath::geometry::RayBase> RAY_S;

			typedef nmath::util::ArrayIndirect<nmath::geometry::PolytopeBase> ARRAY_POLYTOPE;
			typedef std::shared_ptr<ARRAY_POLYTOPE> ARRAY_POLYTOPE_S;

			//typedef nmath::util::ArrayIndirect<nmath::geometry::RayBase> ARRAY_RAY;
			//typedef std::shared_ptr<ARRAY_RAY> ARRAY_RAY_S;

			typedef nmath::util::ArrayIndirect<nspace::light::Base> ARRAY_LIGHT;
			typedef std::shared_ptr<ARRAY_LIGHT> ARRAY_LIGHT_S;


			virtual void												reload_buffer();
			virtual void												render_init();
			virtual void												render();

			//virtual RAY_S												make_ray() = 0;
			

		public:
			ARRAY_POLYTOPE_S											_M_polytopes;
			ARRAY_LIGHT_S												_M_lights;
			//ARRAY_RAY_S													_M_rays;
			
			

			std::vector< std::shared_ptr<nspace::actor::Base> >			_M_actors;
			
			std::shared_ptr<nspace::graphics::raycast::ViewportBase>	_M_viewport;

			std::shared_ptr<nspace::graphics::ManagerBase>				_M_render_manager;

		};
	}
}

#endif