#ifndef NMATH_GRAPH_ITERATOR_VERT_GRAPH
#define NMATH_GRAPH_ITERATOR_VERT_GRAPH

#include <iterator>

#include "../decl.hpp"
#include "../vert.hpp"
#include "../vert_comp.hpp"


namespace nmath {
	namespace graph {
		namespace iterator {

			typedef std::iterator<std::input_iterator_tag, graph::VERT_S> ITERATOR_VERT;

			/**
			 * iterates on each edge in a vert's edge container
			 */
			class vert_graph :
				public ITERATOR_VERT
			{
			public:
				typedef graph::CONT_VERT::iterator iterator;

				typedef graph::VERT_S const &	reference;
				typedef graph::VERT_S		value_type;

				vert_graph(graph::container::vert &, iterator);
				vert_graph			operator=(vert_graph const &);

				void				next();

				graph::iterator::vert_graph	operator++();
				/** postfix */
				graph::iterator::vert_graph	operator++(int);

				reference			operator*();
				value_type const *		operator->();

				bool				operator==(graph::iterator::vert_graph const &);
				bool				operator!=(graph::iterator::vert_graph const &);

				//private:
				graph::container::vert &		_M_container;
				iterator			_M_j;
			};

		}
	}
}

#endif