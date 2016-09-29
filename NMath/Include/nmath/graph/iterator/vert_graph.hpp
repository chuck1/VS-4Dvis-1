#ifndef NMATH_GRAPH_ITERATOR_VERT_GRAPH
#define NMATH_GRAPH_ITERATOR_VERT_GRAPH

#include <iterator>

#include "../decl.hpp"
#include "../vert.hpp"
#include "../vert_comp.hpp"


namespace nmath {
	namespace graph {
		namespace iterator {

			/**
			 * iterates on each edge in a vert's edge container
			 */
			template<typename V>
			class vert_graph :
				public std::iterator<std::input_iterator_tag, std::shared_ptr<V>>
			{
			public:
				typedef typename std::set<std::shared_ptr<V>, graph::vert_comp<V>>::iterator iterator;

				typedef std::shared_ptr<V> const &	reference;
				typedef std::shared_ptr<V>		value_type;

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