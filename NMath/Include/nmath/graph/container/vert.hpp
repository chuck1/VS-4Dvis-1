#ifndef NMATH_GRAPH_CONTAINER_VERT
#define NMATH_GRAPH_CONTAINER_VERT

#include <memory>
#include <set>
#include <vector>

#include "../decl.hpp"
#include "../vert_comp.hpp"

namespace nmath {
	namespace graph {
		namespace container {

			template<typename V>
			class Vert
			{
			public:
				typedef std::shared_ptr<V> V_S;
				typedef std::set<V_S, graph::vert_comp<V>> CONT;

				typedef typename CONT::iterator	iterator;

				/*iterator	begin();
				iterator	end();

				unsigned int	size() const;

				iterator	find(V_S const &);

				iterator	insert(iterator const &, CONT_VERT::value_type &);

				iterator	erase(iterator &);*/








				iterator		begin()
				{
					return _M_container.begin();
				}
				iterator		end()
				{
					return _M_container.end();
				}
				iterator		find(V_S const & v)
				{
					return _M_container.find(v);
				}
				iterator		erase(iterator & i)
				{
					nmath::graph::VERT_W w = *i;

					assert(!w.expired());

					auto ret = _M_container.erase(i);

					assert(w.expired());

					return ret;
				}
				unsigned int	size() const
				{
					//auto s1 = _M_container.size();
					//auto s2 = std::distance(begin(), end());
					return _M_container.size();
				}
				iterator		insert(iterator const & i, typename CONT::value_type & v)
				{
					return _M_container.insert(i, v);
				}








			private:
				CONT	_M_container;
			};

		}
	}
}

#endif