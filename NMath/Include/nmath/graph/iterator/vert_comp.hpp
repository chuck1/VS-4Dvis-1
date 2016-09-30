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
				typedef std::shared_ptr<V> V_S;
				typedef typename std::set<std::shared_ptr<V>, graph::vert_comp<V>>::iterator iterator;

				typedef std::shared_ptr<V> const &	reference;
				typedef std::shared_ptr<V>		value_type;

				//vert_comp(graph::container::vert &, iterator, int);

				//void				next();

				//graph::iterator::vert_comp		operator++();
				///** postfix */
				//graph::iterator::vert_comp		operator++(int);

				//reference			operator*();
				//value_type const *		operator->();

				//bool				operator==(graph::iterator::vert_comp const &);
				//bool				operator!=(graph::iterator::vert_comp const &);





				vert_comp(nmath::graph::container::Vert<V> & container, iterator j, int c) :
					_M_container(container),
					_M_j(j),
					_M_c(c)
				{
					next();
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

						if (v->comp._M_c == _M_c) break;

						//std::cout << "next " << v->comp._M_visited << " " << v->comp._M_c << " != " << _M_c << std::endl;

						++_M_j;
					}
				}
				vert_comp			operator++()
				{
					++_M_j;
					next();
					return nmath::graph::iterator::vert_comp<V>(_M_container, _M_j, _M_c);
				}
				vert_comp			operator++(int)
				{
					nmath::graph::iterator::vert_comp<V> ret(_M_container, _M_j, _M_c);
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

				bool				operator==(vert_comp const & i)
				{
					return (_M_j == i._M_j);
				}
				bool				operator!=(vert_comp const & i)
				{
					return !(_M_j == i._M_j);
				}







			private:
				graph::container::Vert<V> &		_M_container;
				iterator			_M_j;
				int					_M_c;
			};

		}
	}
}

#endif
