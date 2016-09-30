#ifndef NMATH_GRAPH_EDGE
#define NMATH_GRAPH_EDGE

#include <memory>
#include <set>
#include <vector>

#include <nmath/graph/decl.hpp>

template<typename V> bool operator<(nmath::graph::Edge<V> const & x, nmath::graph::Edge<V> const & y);

namespace nmath{
	namespace graph{
		template<typename V>
		class Edge
		{
		public:
			friend bool operator< <>(nmath::graph::Edge<V> const & x, nmath::graph::Edge<V> const & y);

			typedef std::shared_ptr<V> V_S;
			typedef std::weak_ptr<V> V_W;

			//edge();
			/*edge(V_S const & v0, V_S const & v1, EDGE_DATA_S const & data);

			bool			enabled() const;

			bool			operator<(edge const &) const;

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
			

			V_W		_M_v0;
			V_W		_M_v1;
			EDGE_DATA_S		_M_data;
		};
		
	}
}

#endif

