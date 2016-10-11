#ifndef NSPACE_APP_APPTEMPLATE
#define NSPACE_APP_APPTEMPLATE

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

		};

	}
}

#endif