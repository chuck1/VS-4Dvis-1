#ifndef NMATH_GRAPH_ITERATOR_VERTGRAPHALL
#define NMATH_GRAPH_ITERATOR_VERTGRAPHALL

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
			class vert_graph_all :
				public std::iterator<std::input_iterator_tag, std::shared_ptr<V>>
			{
			public:
				typedef typename std::set<std::shared_ptr<V>, graph::vert_comp<V>>::iterator iterator;

				typedef std::shared_ptr<V> V_S;
				typedef V_S const &		reference;
				typedef V_S				value_type;
				typedef std::function<bool(std::shared_ptr<V> const &)> VFUNC;

				vert_graph_all(nmath::graph::container::Vert<V> & container, iterator j) :
					_M_container(container),
					_M_j(j)
				{
					next();
				}
				vert_graph_all(nmath::graph::container::Vert<V> & container, iterator j, VFUNC func) :
					_M_container(container),
					_M_j(j),
					_M_func(func)
				{
					next();
				}
				vert_graph_all			operator=(vert_graph_all const & i)
				{
					_M_container = i._M_container;
					_M_j = i._M_j;
					return *this;
				}

				void					next()
				{
					while (true) {
						if (_M_j == _M_container.end()) break;

						graph::VERT_S const & v = *_M_j;

						assert(v);

						if (_M_func) {
							if (!_M_func(v)) {
								++_M_j;
								continue;
							}
						}

						break;
					}
				}

				vert_graph_all			operator++()
				{
					++_M_j;
					next();
					return graph::iterator::vert_graph_all(_M_container, _M_j);
				}
				vert_graph_all			operator++(int)
				{
					graph::iterator::vert_graph_all ret(_M_container, _M_j);
					operator++();
					return ret;
				}

				reference				operator*()
				{
					return *_M_j;
				}
				value_type const *		operator->()
				{
					return _M_j.operator->();
				}

				bool					operator==(nmath::graph::iterator::vert_graph_all const & i)
				{
					return (_M_j == i._M_j);
				}
				bool					operator!=(nmath::graph::iterator::vert_graph_all const & i)
				{
					return !(_M_j == i._M_j);
				}




				//private:
				graph::container::Vert<V> &		_M_container;
				iterator			_M_j;
				std::function<bool(std::shared_ptr<V> const &)>			_M_func;
			};

		}
	}
}

#endif