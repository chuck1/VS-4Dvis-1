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
<<<<<<< HEAD
			class Vert
			{
			public:
				typedef std::shared_ptr<V> V_S;
				typedef std::weak_ptr<V> V_W;
				typedef std::set<V_S, graph::vert_comp<V>> CONT;

				typedef typename CONT::iterator	iterator;

				/*iterator	begin();
=======
			class Vert<V>
			{
			public:
				typedef std::set<std::shared_ptr<V>, graph::vert_comp> CONT;

				typedef typename CONT::iterator	iterator;

				iterator	begin();
>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3
				iterator	end();

				unsigned int	size() const;

<<<<<<< HEAD
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
					V_W w = *i;

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








=======
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
			class Vert<V>
			{
			public:
				typedef std::set<std::shared_ptr<V>, graph::vert_comp> CONT;

				typedef typename CONT::iterator	iterator;

				iterator	begin();
				iterator	end();

				unsigned int	size() const;

=======
>>>>>>> parent of f68be32... fix merge issue
=======
>>>>>>> parent of f68be32... fix merge issue
=======
>>>>>>> parent of f68be32... fix merge issue
				iterator	find(graph::VERT_S const &);

				iterator	insert(iterator const &, CONT_VERT::value_type &);

				iterator	erase(iterator &);
>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3
			private:
				CONT	_M_container;
			};

		}
	}
}

<<<<<<< HEAD
#endif
=======
#endif
>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3
