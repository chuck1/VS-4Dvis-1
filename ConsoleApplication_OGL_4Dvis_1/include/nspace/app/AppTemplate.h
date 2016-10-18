#ifndef NSPACE_APP_APPTEMPLATE
#define NSPACE_APP_APPTEMPLATE

#include <cstdio>
#include <nmath/util/Util.h>
#include <nspace/app/App.h>
#include <nspace/graphics/raycast/Task.h>
#include <nspace/graphics/OCL.h>

#define APP_RENDER_GPU (1)
#define APP_RENDER_CPU (0)

#define NSPACE_APP_APPTEMPLATE_DEBUG (0)

#define NSPACE_APP_APPTEMPLATE_PROF (1)

namespace nspace {
	namespace app {

		
		template<unsigned int M>
		class App: public AppBase
		{
		public:
		};
	}
}

#endif


