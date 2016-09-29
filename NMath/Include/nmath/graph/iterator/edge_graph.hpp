

#include <iterator>

#include <nmath/graph/decl.hpp>
#include <nmath/graph/vert_comp.hpp>
#include <nmath/graph/edge.hpp>

namespace nmath {
	namespace graph {
		namespace iterator {
			/**
			 * iterates on each unique edge of graph. first iterators on each vert, then
			 * iterates on each edge of the vert's edge container if the opposite vert evaluates to
			 * less than the first vert
			 */
			template<typename V>
			class edge_graph :
				public std::iterator<std::input_iterator_tag, nmath::graph::Edge<V>>
			{
			public:
				typedef nmath::graph::edge const &	reference;
				typedef nmath::graph::edge		value_type;

				typedef nmath::std::set<std::shared_ptr<V>, graph::vert_comp<V>>::iterator iterator0;
				typedef nmath::graph::CONT_EDGE::iterator iterator1;

				edge_graph(nmath::graph::container::vert &, iterator0 const &);
				edge_graph(nmath::graph::container::vert &, iterator0 const &, iterator1 const &);

				edge_graph			operator=(edge_graph const &);

				/** prefix */
				nmath::graph::iterator::edge_graph	operator++();
				/** postfix */
				nmath::graph::iterator::edge_graph	operator++(int);

				void				next();

				reference			operator*();
				value_type const *		operator->();

				bool				operator==(nmath::graph::iterator::edge_graph const &);
				bool				operator!=(nmath::graph::iterator::edge_graph const &);

				//private:
				nmath::graph::container::vert &		_M_container;
				nmath::std::set<std::shared_ptr<V>, graph::vert_comp<V>>::iterator		_M_i;
				nmath::graph::CONT_EDGE::iterator		_M_j;
				//value_type			_M_value;
			};

		}
	}
}