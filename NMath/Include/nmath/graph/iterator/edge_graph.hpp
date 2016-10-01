#ifndef NMATH_GRAPH_ITERATOR_EDGEGRAPH
#define NMATH_GRAPH_ITERATOR_EDGEGRAPH

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
				typedef std::shared_ptr<V> V_S;
				
				typedef nmath::graph::Edge<V> const &	reference;
				typedef nmath::graph::Edge<V>			value_type;
				
				typedef std::set<Edge<V>> CONT;

				typedef typename std::set<V_S, graph::vert_comp<V>>::iterator iterator0;
				typedef typename CONT::iterator iterator1;

				//edge_graph(nmath::graph::container::vert &, iterator0 const &);
				//edge_graph(nmath::graph::container::vert &, iterator0 const &, iterator1 const &);

				//edge_graph			operator=(edge_graph const &);

				///** prefix */
				//nmath::graph::iterator::edge_graph	operator++();
				///** postfix */
				//nmath::graph::iterator::edge_graph	operator++(int);

				//void				next();

				//reference			operator*();
				//value_type const *		operator->();

				//bool				operator==(nmath::graph::iterator::edge_graph const &);
				//bool				operator!=(nmath::graph::iterator::edge_graph const &);




				edge_graph(nmath::graph::container::Vert<V> & container, iterator0 const & i) :
					_M_container(container),
					_M_i(i)
				{
					if (_M_i != _M_container.end()) {
						_M_j = (*_M_i)->_M_edges->begin();
						next();
					}
				}
				edge_graph(nmath::graph::container::Vert<V> & container, iterator0 const & i, iterator1 const & j) :
					_M_container(container),
					_M_i(i),
					_M_j(j)
				{
					next();
				}

				edge_graph			operator=(edge_graph const & i)
				{
					_M_container = i._M_container;
					_M_i = i._M_i;
					_M_j = i._M_j;
					return *this;
				}

				void				next()
				{
					while (true) {
						//std::cout << "iterator edge_graph i " << std::distance(_M_i, _M_container.end()) << std::endl;

						if (_M_i == _M_container.end()) break;

						V_S const & pu = *_M_i;
						V & u = *pu;

						//std::cout << "iterator edge_graph j " << std::distance(_M_j, u._M_edges->end()) << std::endl;

						if (_M_j == u._M_edges->end()) {
							++_M_i;

							if (_M_i == _M_container.end()) break;

							_M_j = (*_M_i)->_M_edges->begin();

							continue;
						}

						nmath::graph::Edge<V> const & edge = *_M_j;

						if (!edge.enabled()) {
							++_M_j;
							continue;
						}

						V_S const & v = _M_j->_M_v1.lock();

						assert(v);

						if (u < (*v)) {
							break;
						}

						++_M_j;
					}
				}
				edge_graph			operator++()
				{
					++_M_j;
					next();
					return THIS(_M_container, _M_i, _M_j);
					//return *this;
				}
				edge_graph			operator++(int)
				{
					edge_graph ret(_M_container, _M_i, _M_j);
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
					//_M_value = *_M_j;
					//return &_M_value;
				}

				bool				operator==(nmath::graph::iterator::edge_graph<V> const & i)
				{
					if (_M_i == i._M_i) {
						if (_M_i == _M_container.end()) return true;

						return _M_j == i._M_j;
					}
					else {
						return false;
					}
				}
				bool				operator!=(nmath::graph::iterator::edge_graph<V> const & i)
				{
					return !(operator==(i));
				}








				typedef std::set<std::shared_ptr<V>, graph::vert_comp<V>> VCONT;
				typedef std::set<Edge<V>> ECONT;

				//private:
				nmath::graph::container::Vert<V> &		_M_container;
				typename VCONT::iterator		_M_i;
				typename ECONT::iterator		_M_j;
				//value_type			_M_value;
			};

		}
	}
}

#endif
