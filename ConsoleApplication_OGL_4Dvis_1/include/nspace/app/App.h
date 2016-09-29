#ifndef NSPACE_APP_APP
#define NSPACE_APP_APP

#include <map>
#include <vector>
#include <memory>

#include <nspace/decl.h>

namespace nspace {
	namespace app {
		class App
		{
		public:
			std::vector< std::shared_ptr<nspace::actor::Base> >		_M_actors;
		};
	}
}

#endif