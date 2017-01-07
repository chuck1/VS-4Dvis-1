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
				typedef std::shared_ptr<V> V_S;
<<<<<<< HEAD
				typedef typename std::set<std::shared_ptr<V>, graph::vert_comp<V>>::iterator iterator;
=======
				typedef typename std::set<std::shared_ptr<V>, nmath::graph::vert_comp<V>>::iterator iterator;
>>>>>>> 268bf01e8f6c31479771525ac3872ff9050934a7

				typedef std::shared_ptr<V> const &	reference;
				typedef std::shared_ptr<V>		value_type;

				//vert_graph(graph::container::vert &, iterator);
				//vert_graph			operator=(vert_graph const &);

				//void				next();

				//graph::iterator::vert_graph	operator++();
				///** postfix */
				//graph::iterator::vert_graph	operator++(int);

				//reference			operator*();
				//value_type const *		operator->();

				//bool				operator==(graph::iterator::vert_graph const &);
				//bool				operator!=(graph::iterator::vert_graph const &);

				vert_graph(nmath::graph::container::Vert<V> & container, iterator j) :
					_M_container(container),
					_M_j(j)
				{
					next();
				}
				vert_graph			operator=(vert_graph const & i)
				{
					_M_container = i._M_container;
					_M_j = i._M_j;
					return *this;
				}

				void				next()
				{
					while (true) {
						if (_M_j == _M_container.end()) break;

						V_S const & v = *_M_j;

						assert(v);

						if (!v->enabled()) {
							++_M_j;
							continue;
						}

						break;
					}
				}
				vert_graph			operator++()
				{
					++_M_j;
					next();
					return nmath::graph::iterator::vert_graph<V>(_M_container, _M_j);
				}
				vert_graph			operator++(int)
				{
<<<<<<< HEAD
					nmath::graph::iterator::vert_graph ret(_M_container, _M_j);
=======
					nmath::graph::iterator::vert_graph<V> ret(_M_container, _M_j);
>>>>>>> 268bf01e8f6c31479771525ac3872ff9050934a7
					operator++();
					return ret;
				}

				reference			operator*()
				{
					return *_M_j;
				}
				value_type const *	operator->()
				{
					return _M_j.operator->();
				}

				bool				operator==(nmath::graph::iterator::vert_graph<V> const & i)
				{
					return (_M_j == i._M_j);
				}
				bool				operator!=(nmath::graph::iterator::vert_graph<V> const & i)
				{
					return !(_M_j == i._M_j);
				}


				//private:
<<<<<<< HEAD
				graph::container::Vert<V> &		_M_container;
=======
				nmath::graph::container::Vert<V> &		_M_container;
>>>>>>> 268bf01e8f6c31479771525ac3872ff9050934a7
				iterator			_M_j;
			};

		}
	}
}

#endif
