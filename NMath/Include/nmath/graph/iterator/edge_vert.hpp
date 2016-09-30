#ifndef NMATH_GRAPH_EDGE_VERT
#define NMATH_GRAPH_EDGE_VERT

#include <iterator>

#include <nmath/graph/decl.hpp>
//#include <nmath/graph/edge.hpp>

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
				
				typedef typename CONT::iterator iterator;

				typedef graph::Edge<V> const &	reference;
				typedef graph::Edge<V>		value_type;

				//edge_vert(graph::container::edge &, iterator);
				//edge_vert &			operator=(edge_vert const &);

				//void				next();

				//graph::iterator::edge_vert		operator++();
				///** postfix */
				//graph::iterator::edge_vert		operator++(int);

				//reference			operator*();
				//value_type const *		operator->();

				//bool				operator==(graph::iterator::edge_vert const &);
				//bool				operator!=(graph::iterator::edge_vert const &);






				edge_vert(nmath::graph::container::Edge<V> & c, iterator i) :
					_M_container(c),
					_M_i(i)
				{
					next();
				}
				edge_vert &				operator=(edge_vert const & i)
				{
					_M_container = i._M_container;
					_M_i = i._M_i;
					return *this;
				}

				void				next()
				{
					while (true) {
						if (_M_i == _M_container.end()) break;

						nmath::graph::Edge<V> const & edge = *_M_i;

						if (!edge.enabled()) {
							++_M_i;
							continue;
						}

						break;
					}
				}
				edge_vert			operator++()
				{
					++_M_i;
					next();
					return THIS(_M_container, _M_i);
				}
				edge_vert			operator++(int)
				{
					edge_vert ret(_M_container, _M_i);
					operator++();
					return ret;
				}

				reference			operator*()
				{
					return *_M_i;
				}
				value_type const *	operator->()
				{
					return _M_i.operator->();
				}

				bool				operator==(edge_vert const & i)
				{
					return _M_i == i._M_i;
				}
				bool				operator!=(edge_vert const & i)
				{
					return !operator==(i);
				}





				//private:
				graph::container::Edge<V> &		_M_container;
				iterator						_M_i;
			};


		}
	}
}

#endif
