#ifndef NMATH_GRAPH_EDGE
#define NMATH_GRAPH_EDGE

#include <memory>
#include <set>
#include <vector>

<<<<<<< HEAD
#include <nmath/graph/decl.hpp>

template<typename V> bool operator<(nmath::graph::Edge<V> const & x, nmath::graph::Edge<V> const & y);
=======
#include "../graph/decl.hpp"
>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3

namespace nmath{
	namespace graph{
		template<typename V>
<<<<<<< HEAD
		class Edge
		{
		public:
			friend bool operator< <>(nmath::graph::Edge<V> const & x, nmath::graph::Edge<V> const & y);

=======
		class edge
		{
		public:
>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3
			typedef std::shared_ptr<V> V_S;
			typedef std::weak_ptr<V> V_W;

			//edge();
<<<<<<< HEAD
			/*edge(V_S const & v0, V_S const & v1, EDGE_DATA_S const & data);
=======
			edge(V_S const & v0, V_S const & v1, EDGE_DATA_S const & data);
>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3

			bool			enabled() const;

			bool			operator<(edge const &) const;
<<<<<<< HEAD

			bool			operator==(edge const &) const;*/


			Edge(V_S const & v0, V_S const & v1, nmath::graph::EDGE_DATA_S const & data) :
				_M_v0(v0),
				_M_v1(v1),
				_M_data(data)
			{
				//	std::cout << "edge ctor" << std::endl;
				assert(v0);
				assert(v1);
			}
			bool			enabled() const
			{
				//assert(!_M_v0.expired());
				if (_M_v0.expired()) return false;

				if (_M_v1.expired()) return false;

				auto const & v0 = _M_v0.lock();
				auto const & v1 = _M_v1.lock();

				if (!v0->enabled()) return false;

				if (!v1->enabled()) return false;

				if (!_M_data->_M_enabled) return false;

				return true;
			}
			
=======
			bool			operator==(edge const &) const;
>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3

			V_W		_M_v0;
			V_W		_M_v1;
			EDGE_DATA_S		_M_data;
		};
		
	}
}

#endif

