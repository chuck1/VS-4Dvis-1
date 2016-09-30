<<<<<<< HEAD
#ifndef NMATH_GRAPH_ITERATOR_VERTGRAPHALL
#define NMATH_GRAPH_ITERATOR_VERTGRAPHALL
=======

>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3

#include <iterator>

#include "../decl.hpp"
#include "../vert.hpp"
<<<<<<< HEAD
#include <nmath/graph/iterator/vert_comp.hpp>
=======
#include "../vert_comp.hpp"
>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3


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
<<<<<<< HEAD
				typedef std::function<bool(std::shared_ptr<V> const &)> VFUNC;

				vert_graph_all(nmath::graph::container::Vert<V> & container, iterator j) :
=======


				vert_graph_all(nmath::graph::container::vert & container, THIS::iterator j) :
>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3
					_M_container(container),
					_M_j(j)
				{
					next();
				}
<<<<<<< HEAD
				vert_graph_all(nmath::graph::container::Vert<V> & container, iterator j, VFUNC func) :
=======
				vert_graph_all(nmath::graph::container::vert & container, THIS::iterator j, nmath::graph::VERT_FUNC func) :
>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3
					_M_container(container),
					_M_j(j),
					_M_func(func)
				{
					next();
				}
<<<<<<< HEAD
				vert_graph_all			operator=(vert_graph_all const & i)
=======
				vert_graph_all			operator=(THIS const & i)
>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3
				{
					_M_container = i._M_container;
					_M_j = i._M_j;
					return *this;
				}

				void					next()
				{
					while (true) {
						if (_M_j == _M_container.end()) break;

<<<<<<< HEAD
						V_S const & v = *_M_j;
=======
						graph::VERT_S const & v = *_M_j;
>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3

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
<<<<<<< HEAD
					return graph::iterator::vert_graph_all<V>(_M_container, _M_j);
				}
				vert_graph_all			operator++(int)
				{
					graph::iterator::vert_graph_all<V> ret(_M_container, _M_j);
=======
					return graph::iterator::vert_graph_all(_M_container, _M_j);
				}
				vert_graph_all			operator++(int)
				{
					graph::iterator::vert_graph_all ret(_M_container, _M_j);
>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3
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

<<<<<<< HEAD
				bool					operator==(nmath::graph::iterator::vert_graph_all<V> const & i)
				{
					return (_M_j == i._M_j);
				}
				bool					operator!=(nmath::graph::iterator::vert_graph_all<V> const & i)
=======
				bool					operator==(nmath::graph::iterator::vert_graph_all const & i)
				{
					return (_M_j == i._M_j);
				}
				bool					operator!=(nmath::graph::iterator::vert_graph_all const & i)
>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3
				{
					return !(_M_j == i._M_j);
				}




				//private:
<<<<<<< HEAD
				graph::container::Vert<V> &		_M_container;
=======
				graph::container::vert &		_M_container;
>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3
				iterator			_M_j;
				std::function<bool(std::shared_ptr<V> const &)>			_M_func;
			};

		}
	}
<<<<<<< HEAD
}

#endif
=======
}
>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3
