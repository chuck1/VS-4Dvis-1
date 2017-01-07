#ifndef NMATH_GRAPH_VERTFUNCTION
#define NMATH_GRAPH_VERTFUNCTION

<<<<<<< HEAD


#endif
=======
#include <nmath/graph/EdgeFunction.h>

namespace nmath {
	namespace graph {
		namespace vert {
			template<typename V>
			void				add_edge(
				V & v,
				std::shared_ptr<V> v0,
				std::shared_ptr<V> v1,
				std::shared_ptr<nmath::graph::edge_data> const & edge_data)
			{
				assert(v._M_edges);

				nmath::graph::Edge<V> edge(v0, v1, edge_data);
				
				//_M_edges->insert(std::move(edge));
				nmath::graph::edge::insert(*v._M_edges, std::move(edge));
			}

		}
	}
}

#endif
>>>>>>> 268bf01e8f6c31479771525ac3872ff9050934a7
