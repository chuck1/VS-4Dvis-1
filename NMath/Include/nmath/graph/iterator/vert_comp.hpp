#ifndef NMATH_GRAPH_ITERATOR_VERT_COMP
#define NMATH_GRAPH_ITERATOR_VERT_COMP

#include <iterator>

#include <nmath/graph/decl.hpp>
#include <nmath/graph/vert.hpp>
#include <nmath/graph/vert_comp.hpp>

namespace nmath {
	namespace graph {
		namespace iterator {

			typedef std::iterator<std::input_iterator_tag, graph::VERT_S> ITERATOR_VERT;

			/**
			 * iterates on each edge in a vert's edge container
			 */
			class vert_comp :
				public ITERATOR_VERT
			{
			public:
				typedef graph::CONT_VERT::iterator iterator;

				typedef graph::VERT_S const &	reference;
				typedef graph::VERT_S		value_type;

				vert_comp(graph::container::vert &, iterator, int);

				void				next();

				graph::iterator::vert_comp		operator++();
				/** postfix */
				graph::iterator::vert_comp		operator++(int);

				reference			operator*();
				value_type const *		operator->();

				bool				operator==(graph::iterator::vert_comp const &);
				bool				operator!=(graph::iterator::vert_comp const &);

			private:
				graph::container::vert &		_M_container;
				iterator			_M_j;
				int				_M_c;
			};

		}
	}
}

#endif