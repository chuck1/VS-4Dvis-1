
#ifndef NMATH_GRAPH_VERT_COMP
#define NMATH_GRAPH_VERT_COMP

#include <memory>
#include <set>
#include <vector>

#include "../graph/decl.hpp"

namespace nmath{
	namespace graph{

		class vert_comp
		{
		public:
			bool	operator()(VERT_S const & np0, VERT_S const & np1);
		};

	}
}

#endif