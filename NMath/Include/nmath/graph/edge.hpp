#ifndef NMATH_GRAPH_EDGE
#define NMATH_GRAPH_EDGE

#include <memory>
#include <set>
#include <vector>

#include "../graph/decl.hpp"

namespace nmath{
	namespace graph{
		template<typename V>
		class edge
		{
		public:
			typedef std::shared_ptr<V> V_S;
			typedef std::weak_ptr<V> V_W;

			//edge();
			edge(V_S const & v0, V_S const & v1, EDGE_DATA_S const & data);

			bool			enabled() const;

			bool			operator<(edge const &) const;
			bool			operator==(edge const &) const;

			V_W		_M_v0;
			V_W		_M_v1;
			EDGE_DATA_S		_M_data;
		};
		
	}
}

#endif

