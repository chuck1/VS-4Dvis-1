<<<<<<< HEAD
#ifndef NMATH_GRAPH_CONTAINER_EDGE
#define NMATH_GRAPH_CONTAINER_EDGE
=======

>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3

#include <memory>
#include <set>
#include <vector>

<<<<<<< HEAD
#include <nmath/graph/decl.hpp>
#include <nmath/graph/EdgeFunction.h>
=======
#include "../../graph/decl.hpp"

>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3

namespace nmath {
	namespace graph {
		namespace container {

			template<typename V>
			class Edge
			{
			public:
<<<<<<< HEAD
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






/*
=======
				typedef std::set<Edge<V>> CONT_EDGE;
				typedef typename CONT_EDGE::iterator ITER;

>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3
				ITER	begin() const;
				ITER	end() const;

				ITER	erase(ITER const &);

				ITER	find(std::shared_ptr<V> const &) const;

				std::pair<typename ITER, bool>	insert(graph::Edge<V> const &);

<<<<<<< HEAD
				typename CONT_EDGE::size_type	size() const;*/

				E_C<V>				_M_container;
			};
		}
	}
}

#endif
=======
				typename CONT_EDGE::size_type	size() const;
<<<<<<< HEAD

<<<<<<< HEAD
=======
				typename CONT_EDGE::size_type	size() const;

=======
>>>>>>> parent of f68be32... fix merge issue
=======

>>>>>>> parent of f68be32... fix merge issue
				CONT_EDGE				_M_container;
			};
		}
	}
}
>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3
