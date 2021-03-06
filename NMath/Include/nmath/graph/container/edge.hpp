#ifndef NMATH_GRAPH_CONTAINER_EDGE
#define NMATH_GRAPH_CONTAINER_EDGE

#include <memory>
#include <set>
#include <vector>

#include <nmath/graph/decl.hpp>
#include <nmath/graph/EdgeFunction.h>

namespace nmath {
	namespace graph {
		namespace container {

			template<typename V>
			class Edge
			{
			public:
<<<<<<< HEAD
				typedef std::set<nmath::graph::Edge<V>> ECONT;
				typedef typename ECONT::iterator iterator;
				typedef std::shared_ptr<V> V_S;



				Edge<V>(){}
				iterator	begin() const
				{
					return _M_container.begin();
				}
				iterator	end() const
				{
					return _M_container.end();
				}
				iterator	erase(iterator const & it)
				{
					return _M_container.erase(it);
				}
				iterator	find(V_S const & u) const
				{
					for (auto it = begin(); it != end(); ++it) {
						nmath::graph::edge const & edge = *it;
						nmath::graph::VERT_S v = edge._M_v1.lock();
						if ((*v) == (*u)) return it;
					}
					return end();
				}
				std::pair<typename ECONT::iterator, bool>	insert(nmath::graph::Edge<V> const & e)
				{
					return _M_container.insert(e);
				}
				typename ECONT::size_type			size() const
				{
					return _M_container.size();
				}






/*
				ITER	begin() const;
				ITER	end() const;
=======
				typedef typename E_C<V>::iterator iterator;
				typedef std::shared_ptr<V> V_S;



				Edge<V>(){}
				iterator	begin() const
				{
					return _M_container.begin();
				}
				iterator	end() const
				{
					return _M_container.end();
				}
				iterator	erase(iterator const & it)
				{
					return _M_container.erase(it);
				}
				iterator	find(V_S const & u) const
				{
					for (auto it = begin(); it != end(); ++it) {
						nmath::graph::Edge<V> const & edge = *it;
						V_S v = edge._M_v1.lock();
						if ((*v) == (*u)) return it;
					}
					return end();
				}
				/*
				std::pair<typename E_C<V>::iterator, bool>	insert(nmath::graph::Edge<V> const & e)
				{
					return _M_container.insert(e);
				}
				*/
				typename E_C<V>::size_type			size() const
				{
					return _M_container.size();
				}
>>>>>>> 268bf01e8f6c31479771525ac3872ff9050934a7




<<<<<<< HEAD
				typename CONT_EDGE::size_type	size() const;*/

				ECONT				_M_container;
=======



				E_C<V>				_M_container;
>>>>>>> 268bf01e8f6c31479771525ac3872ff9050934a7
			};
		}
	}
}

<<<<<<< HEAD
#endif
=======
#endif

>>>>>>> 268bf01e8f6c31479771525ac3872ff9050934a7
