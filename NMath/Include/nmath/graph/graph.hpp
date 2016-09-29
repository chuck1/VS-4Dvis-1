

#include <memory>
#include <set>
#include <vector>

#include <nmath/graph/decl.hpp>
#include <nmath/graph/iterator/vert_comp.hpp>
#include <nmath/graph/iterator/vert_graph.hpp>
#include <nmath/graph/iterator/vert_graph_all.hpp>
#include <nmath/graph/container/vert.hpp>

namespace nmath {
	namespace graph {

		template<typename VERT>
		class Graph : public std::enable_shared_from_this<Graph>
		{
		public:
			typedef std::shared_ptr<VERT> VERT_S;

			void				add_edge_util(VERT_S v0, VERT_S v1, std::shared_ptr<graph::edge_data> const &);
			void				add_edge(VERT_S v0, VERT_S v1);

			void				edge_enable();
			void				vert_enable();

			/** vert functions */

			//graph::iterator::vert_graph		iter(std::shared_ptr<V> v);

			//graph::iterator::vert_graph		vert_find(std::shared_ptr<V> v);
			//graph::iterator::vert_graph		vert_erase(graph::iterator::vert_graph &);
			//void							vert_erase_layer(unsigned int l);

			//graph::iterator::vert_graph_all	vert_begin_all(VERT_FUNC);
			//graph::iterator::vert_graph_all	vert_end_all(VERT_FUNC);
			//graph::iterator::vert_graph_all	vert_begin_all();
			//graph::iterator::vert_graph_all	vert_end_all();
			//graph::iterator::vert_graph		vert_begin();
			//graph::iterator::vert_graph		vert_end();

			//unsigned int			vert_size();

			//graph::iterator::vert_comp		comp_vert_begin(int);
			//graph::iterator::vert_comp		comp_vert_end(int);


			///** edge functions */

			//graph::iterator::edge_graph	edge_begin();
			//graph::iterator::edge_graph	edge_end();

			//void				edge_erase();

			//void				edge_erase_util(VERT_S &, VERT_S &);
			//void				edge_erase(VERT_S &, VERT_S &);

			//graph::iterator::edge_graph	edge_erase(graph::iterator::edge_graph);

			///** algorithms */

			//void				distance_util(std::shared_ptr<V>);
			//void				distance(std::shared_ptr<V> const &);

			//void				bridges_sub(VERT_S const & n, int & t, std::vector<graph::edge> & ret);
			//std::vector<graph::edge>		bridges();

			//void				components_util(VERT_S const & n, int c);
			//int				components();
			//void				component(int c);

			//void				dot();

			//void				layer_move(unsigned int, unsigned int);

			std::vector<graph::LAYER_S>	_M_layers;

			graph::container::vert		_M_verts;
		};

	}
}