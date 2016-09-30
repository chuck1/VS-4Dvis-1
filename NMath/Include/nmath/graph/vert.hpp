#ifndef NMATH_GRAPH_VERT
#define NMATH_GRAPH_VERT

#include <memory>
#include <set>
#include <vector>

#include <nmath/graph/decl.hpp>
//#include <nmath/graph/edge.hpp>
#include <nmath/graph/iterator/edge_vert.hpp>
//#include <nmath/graph/container/edge.hpp>
#include <nmath/graph/layer.hpp>

namespace nmath {
	namespace graph {

		template<typename V>
		class Vert : public std::enable_shared_from_this<Vert<V>>
		{
		public:
			friend class graph::iterator::edge_graph<V>;

			typedef std::shared_ptr<V> V_S;
			typedef std::weak_ptr<V> V_W;

			typedef std::shared_ptr<Graph<V>> G_S;
			typedef std::weak_ptr<Graph<V>> G_W;

			typedef graph::container::Edge<V> ECONT;
			typedef std::shared_ptr<ECONT> ECONT_S;

			Vert(G_S g, ECONT_S c) :
				_M_enabled(true),
				_M_graph(g),
				_M_edges(c)
			{
			}
			virtual ~Vert()
			{
				//	std::cout << "vert destroyed" << std::endl;
			}
			bool				enabled() const
			{
				if (!_M_enabled) return false;

				if (!_M_layer.expired()) {
					if (!_M_layer.lock()->_M_enabled) return false;
				}

				return true;
			}
			G_S					get_graph()
			{
				auto ret = _M_graph.lock();
				assert(ret);
				return ret;
			}
			nmath::graph::iterator::edge_vert<V>		edge_begin()
			{
				return nmath::graph::iterator::edge_vert(*_M_edges, _M_edges->begin());
			}
			nmath::graph::iterator::edge_vert<V>		edge_end()
			{
				return nmath::graph::iterator::edge_vert(*_M_edges, _M_edges->end());
			}
			nmath::graph::iterator::edge_vert<V>		edge_erase(nmath::graph::iterator::edge_vert<V> & i)
			{
				auto j = _M_edges->erase(i._M_i);

				return nmath::graph::iterator::edge_vert(*_M_edges, j);
			}

			void				edge_erase_disconnected()
			{
				for (auto i = edge_begin(); i != edge_end();) {

					if (i->_M_v0.expired()) throw std::exception();

					if (i->_M_v1.expired()) {
						//std::cout << "graph::vert erase edge" << std::endl;
						i = edge_erase(i);
					}
					else {
						++i;
					}
				}
			}
			unsigned int			edge_size()
			{
				return std::distance(edge_begin(), edge_end());
			}
			void				add_edge_util(
				V_S v0,
				V_S v1,
				std::shared_ptr<nmath::graph::edge_data> const & edge_data)
			{
				assert(_M_edges);

				nmath::graph::Edge<V> edge(v0, v1, edge_data);

				_M_edges->insert(std::move(edge));
			}
			void				edge_erase_util(V_S & v0, V_S & v1)
			{
				//graph::container::EDGE_S const & edges = (*i)->_M_edges;

				auto j = _M_edges->find(v1);
				//auto j = std::find(edges.begin(), edges.end(), v1);

				if (j == _M_edges->end()) throw std::exception();

				_M_edges->erase(j);

				//for(auto j = edges.begin(); j != edges.end(); ++j) {
				//	graph::VERT_S w = j->first.lock();
				//}
			}

			virtual bool		operator==(V const & x) = 0;
			virtual bool		operator<(V const & x) = 0;

			/////////////////////////////////////////

			// data
			bool				_M_enabled;

			// for ditance algorithm
			struct {
				double		_M_distance;
			} dist;

			// for bridge-finding algorithm
			struct {
				int				_M_disc;
				int				_M_low;
				bool			_M_visited;
				V_W				_M_parent;
			} bridge;

			// for marking components
			struct {
				bool					_M_visited;
				int						_M_c;
			} comp;
			
			G_W							_M_graph;
			
			std::shared_ptr<graph::container::Edge<V>>	_M_edges;
		public:
			LAYER_W						_M_layer;
		};

	}
}

#endif