
#ifndef NMATH_GRAPH_VERT_COMP
#define NMATH_GRAPH_VERT_COMP

#include <memory>
#include <set>
#include <vector>

#include "../graph/decl.hpp"

namespace nmath{
	namespace graph{
		template<typename V>
		class vert_comp
		{
		public:
			bool	operator()(std::shared_ptr<V> const & np0, std::shared_ptr<V> const & np1)
			{
				return (*np0) < (*np1);
			}
		};

	}
}

#endif