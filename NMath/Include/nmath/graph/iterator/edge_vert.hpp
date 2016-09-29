#ifndef NMATH_GRAPH_EDGE_VERT
#define NMATH_GRAPH_EDGE_VERT

#include <iterator>

#include <nmath/graph/decl.hpp>
#include <nmath/graph/edge.hpp>

namespace nmath {
	namespace graph {
		namespace iterator {
			/**
			 * iterates on each edge in a vert's edge container
			 */
			template<typename V>
			class edge_vert :
				public std::iterator<std::input_iterator_tag, graph::Edge<V>>
			{
			public:
				//typedef typename graph::CONT_EDGE::iterator iterator;
				typedef std::iterator<std::input_iterator_tag, graph::Edge<V>> CONT;
				
				typedef CONT::iterator iterator;

				typedef graph::edge const &	reference;
				typedef graph::edge		value_type;

				edge_vert(graph::container::edge &, iterator);
				edge_vert &			operator=(edge_vert const &);

				void				next();

				graph::iterator::edge_vert		operator++();
				/** postfix */
				graph::iterator::edge_vert		operator++(int);

				reference			operator*();
				value_type const *		operator->();

				bool				operator==(graph::iterator::edge_vert const &);
				bool				operator!=(graph::iterator::edge_vert const &);

				//private:
				graph::container::edge &		_M_container;
				iterator						_M_i;
			};


		}
	}
}

#endif