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
			class Vert<V>
			{
			public:
				typedef std::set<std::shared_ptr<V>, graph::vert_comp> CONT;

				typedef typename CONT::iterator	iterator;

				iterator	begin();
				iterator	end();

				unsigned int	size() const;

				iterator	find(graph::VERT_S const &);

				iterator	insert(iterator const &, CONT_VERT::value_type &);

				iterator	erase(iterator &);
			private:
				CONT	_M_container;
			};

		}
	}
}

#endif