

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
			class vert_graph_all :
				public ITERATOR_VERT
			{
			public:
				typedef graph::CONT_VERT::iterator iterator;

				typedef graph::VERT_S const &	reference;
				typedef graph::VERT_S		value_type;

				vert_graph_all(graph::container::vert &, iterator);
				vert_graph_all(graph::container::vert &, iterator, graph::VERT_FUNC);

				vert_graph_all			operator=(vert_graph_all const &);

				void				next();

				graph::iterator::vert_graph_all	operator++();
				/** postfix */
				graph::iterator::vert_graph_all	operator++(int);

				reference			operator*();
				value_type const *		operator->();

				bool				operator==(graph::iterator::vert_graph_all const &);
				bool				operator!=(graph::iterator::vert_graph_all const &);

				//private:
				graph::container::vert &		_M_container;
				iterator			_M_j;
				graph::VERT_FUNC			_M_func;
			};

		}
	}
}