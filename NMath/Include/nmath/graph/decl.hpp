#ifndef NMATH_GRAPH_DECL
#define NMATH_GRAPH_DECL

#include <set>
#include <vector>
#include <memory>
#include <functional>

namespace nmath{
	namespace graph{
		template<typename V>
		class Vert;

		template<typename V>
		class Edge;

		template<typename V>
		class vert_comp;
		//class pair_comp;

		class edge_data;

		//class pair;
		template<typename VERT>
		class Graph;

		class layer;

		typedef std::shared_ptr<layer>	LAYER_S;
		typedef std::weak_ptr<layer>	LAYER_W;

		namespace container {
			template<typename V>
			class Edge;

			template<typename V>
			class Vert;
		}

		namespace iterator {
			template<typename V>
			class edge_graph;
			template<typename V>
			class edge_vert;
		}

		typedef edge_data				EDGE_DATA;

		typedef std::shared_ptr<EDGE_DATA>		EDGE_DATA_S;

		namespace edge {
			template<typename V> class less;
		}

		template<typename V>
		using E_C = std::set<nmath::graph::Edge<V>, nmath::graph::edge::less<V>>;

		//typedef std::set<edge<V>>				std::set<edge<V>>;
		

		//typedef std::set<std::shared_ptr<V>, graph::vert_comp>	CONT_VERT;

		//typedef std::function<bool(std::shared_ptr<V> const &)>	VERT_FUNC;

	}
}

#endif
