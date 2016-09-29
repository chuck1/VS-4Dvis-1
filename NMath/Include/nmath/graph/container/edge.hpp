

#include <memory>
#include <set>
#include <vector>

#include "../../graph/decl.hpp"


namespace nmath {
	namespace graph {
		namespace container {

			template<typename V>
			class Edge
			{
			public:
				typedef std::set<Edge<V>> CONT_EDGE;
				typedef typename CONT_EDGE::iterator ITER;

				ITER	begin() const;
				ITER	end() const;

				ITER	erase(ITER const &);

				ITER	find(std::shared_ptr<V> const &) const;

				std::pair<typename ITER, bool>	insert(graph::Edge<V> const &);

				typename CONT_EDGE::size_type	size() const;

				CONT_EDGE				_M_container;
			};
		}
	}
}