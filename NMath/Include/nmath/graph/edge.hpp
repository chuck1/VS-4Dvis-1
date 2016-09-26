#ifndef NMATH_GRAPH_EDGE
#define NMATH_GRAPH_EDGE

#include <memory>
#include <set>
#include <vector>

#include "../graph/decl.hpp"

namespace nmath{
	namespace graph{

		class edge
		{
		public:
			//edge();
			edge(graph::VERT_S const & v0, graph::VERT_S const & v1, EDGE_DATA_S const & data);

			bool			enabled() const;

			bool			operator<(edge const &) const;
			bool			operator==(edge const &) const;

			graph::VERT_W		_M_v0;
			graph::VERT_W		_M_v1;
			EDGE_DATA_S		_M_data;
		};
		
	}
}

#endif

