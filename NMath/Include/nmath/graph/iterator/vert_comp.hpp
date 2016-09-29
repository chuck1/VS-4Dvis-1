#ifndef NMATH_GRAPH_ITERATOR_VERT_COMP
#define NMATH_GRAPH_ITERATOR_VERT_COMP

#include <iterator>

#include <nmath/graph/decl.hpp>
#include <nmath/graph/vert.hpp>
#include <nmath/graph/vert_comp.hpp>

namespace nmath {
	namespace graph {
		namespace iterator {

			/**
			 * iterates on each edge in a vert's edge container
			 */
			template<typename V>
			class vert_comp : public std::iterator<std::input_iterator_tag, std::shared_ptr<V>>
			{
			public:
				typedef typename std::set<std::shared_ptr<V>, graph::vert_comp<V>>::iterator iterator;

				typedef std::shared_ptr<V> const &	reference;
				typedef std::shared_ptr<V>		value_type;

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