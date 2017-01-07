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
<<<<<<< HEAD
				typedef std::set<V_S, graph::vert_comp<V>> CONT;

				typedef typename CONT::iterator	iterator;

				/*iterator	begin();
				iterator	end();
=======
				typedef std::weak_ptr<V> V_W;
				typedef std::set<V_S, nmath::graph::vert_comp<V>> CONT;

				typedef typename CONT::iterator	iterator;

>>>>>>> 268bf01e8f6c31479771525ac3872ff9050934a7


<<<<<<< HEAD
				iterator	find(V_S const &);
=======
>>>>>>> 268bf01e8f6c31479771525ac3872ff9050934a7


<<<<<<< HEAD
				iterator	erase(iterator &);*/





=======
>>>>>>> 268bf01e8f6c31479771525ac3872ff9050934a7



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
<<<<<<< HEAD
					nmath::graph::VERT_W w = *i;
=======
					V_W w = *i;
>>>>>>> 268bf01e8f6c31479771525ac3872ff9050934a7

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





<<<<<<< HEAD



=======
>>>>>>> 268bf01e8f6c31479771525ac3872ff9050934a7
			private:
				CONT	_M_container;
			};

		}
	}
}

#endif
