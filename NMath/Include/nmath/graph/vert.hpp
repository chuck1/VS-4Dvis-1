#ifndef NMATH_GRAPH_VERT
#define NMATH_GRAPH_VERT

#include <memory>
#include <set>
#include <vector>

#include <nmath/graph/decl.hpp>
#include <nmath/graph/iterator/edge_vert.hpp>

namespace nmath{
	namespace graph{

		class vert : public std::enable_shared_from_this<vert>
		{
		public:
			friend class graph::iterator::edge_graph;

			vert(GRAPH_S);
			virtual ~vert();

			bool			enabled() const;

			GRAPH_S			get_graph();

			/*
			std::vector<S_Edge>	get_edges();
			S_Node			get_other(graph::S_Edge e);
			SET_Node		get_adjacent_verts();
			VEC_PAIR		get_adjacent();
			*/

			graph::iterator::edge_vert	edge_begin();
			graph::iterator::edge_vert	edge_end();
			graph::iterator::edge_vert	edge_erase(graph::iterator::edge_vert &);

			unsigned int		edge_size();

			void				edge_erase_disconnected();

			void				add_edge_util(
					graph::VERT_S v0,
					graph::VERT_S v1,
					std::shared_ptr<graph::edge_data> const & edge_data);
			void				edge_erase_util(graph::VERT_S & v0, graph::VERT_S & v1);

			virtual bool		operator==(vert const &) = 0;
			virtual bool		operator<(vert const &) = 0;

			/////////////////////////////////////////

			// data
			bool				_M_enabled;

			// for ditance algorithm
			struct {
				double		_M_distance;
			} dist;

			// for bridge-finding algorithm
			struct {
				int		_M_disc;
				int		_M_low;
				bool		_M_visited;
				VERT_W		_M_parent;
			} bridge;

			// for marking components
			struct {
				bool		_M_visited;
				int		_M_c;
			} comp;


			// private

			GRAPH_W			_M_graph;
			//private:	
			graph::container::EDGE_S	_M_edges;
		public:
			LAYER_W			_M_layer;
		};

	}
}

#endif