#ifndef NMATH_GRAPH_GRAPHFUNCTION
#define NMATH_GRAPH_GRAPHFUNCTION

namespace nmath {
	namespace graph {
		namespace graph {
			template<typename V>
			void		add_edge(
					nmath::graph::Graph<V> & g,
					std::shared_ptr<V> v0,
					std::shared_ptr<V> v1,
					std::shared_ptr<nmath::graph::edge_data> const & edge_data)
			{
				auto i = g.iter(v0);
				//(*i)->add_edge_util(v0, v1, edge_data);
				nmath::graph::vert::add_edge(**i, v0, v1, edge_data);
			}
			template<typename V>
			void		add_edge(
					nmath::graph::Graph<V> & g,
					std::shared_ptr<V> v0,
					std::shared_ptr<V> v1)
			{
				auto data = std::make_shared<nmath::graph::edge_data>();
				
				add_edge<V>(g, v0, v1, data);
				add_edge<V>(g, v1, v0, data);

				//nmath::graph::graph::add_edge(g, v0, v1, data);
				//nmath::graph::graph::add_edge(g, v1, v0, data);
				//nmath::graph::vert::add_edge(v0, v1, data);
				//add_edge_util(v1, v0, data);
			}
		}
	}
}

#endif
