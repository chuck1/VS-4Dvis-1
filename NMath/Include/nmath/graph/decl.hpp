#ifndef NMATH_GRAPH_DECL
#define NMATH_GRAPH_DECL

#include <set>
#include <vector>
#include <memory>
#include <functional>

namespace nmath{
	namespace graph{

		class vert;
		class edge;

		class vert_comp;
		//class pair_comp;

		class edge_data;

		//class pair;

		class Graph;

		class layer;

		typedef std::shared_ptr<layer>	LAYER_S;
		typedef std::weak_ptr<layer>	LAYER_W;

		namespace container {
			class edge;
			class vert;

			typedef std::shared_ptr<edge> EDGE_S;
		}

		namespace iterator {
			class edge_graph;
			class edge_vert;
		}

		typedef std::shared_ptr<Graph>			GRAPH_S;
		typedef std::weak_ptr<Graph>			GRAPH_W;

		typedef vert					VERT;
		typedef edge					EDGE;
		typedef edge_data				EDGE_DATA;


		typedef std::shared_ptr<EDGE>			EDGE_S;

		typedef std::shared_ptr<VERT>			VERT_S;
		typedef std::weak_ptr<VERT>			VERT_W;

		typedef std::shared_ptr<EDGE_DATA>		EDGE_DATA_S;


		typedef std::set<edge>				CONT_EDGE;
		//typedef container::edge			CONT_EDGE;

		typedef std::set<graph::VERT_S, graph::vert_comp>	CONT_VERT;

		typedef std::function<bool(graph::VERT_S const &)>	VERT_FUNC;

	}
}

#endif