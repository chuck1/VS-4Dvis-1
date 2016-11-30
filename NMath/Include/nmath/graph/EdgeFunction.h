#ifndef NMATH_GRAPH_EDGEFUNCTION
#define NMATH_GRAPH_EDGEFUNCTION

#include <nmath/graph/edge.hpp>
#include <nmath/graph/vert.hpp>

namespace nmath {
	namespace graph {

	}
}

template<typename V>
bool			operator==(nmath::graph::Edge<V> const & x, nmath::graph::Edge<V> const & y)
{
	typedef std::shared_ptr<V> V_S;

	V_S pv00 = x._M_v0.lock();
	V_S pv01 = y._M_v0.lock();
	V_S pv10 = x._M_v1.lock();
	V_S pv11 = y._M_v1.lock();
	V & v00 = *pv00;
	V & v01 = *pv01;
	V & v10 = *pv10;
	V & v11 = *pv11;

	return (v00 == v01) && (v10 == v11);
}
template<typename V>
bool			operator<(nmath::graph::Edge<V> const & x, nmath::graph::Edge<V> const & y)
{
	typedef std::shared_ptr<V> V_S;

	V_S pv00 = x._M_v0.lock();
	V_S pv01 = y._M_v0.lock();
	V_S pv10 = x._M_v1.lock();
	V_S pv11 = y._M_v1.lock();
	V & v00 = *pv00;
	V & v01 = *pv01;
	V & v10 = *pv10;
	V & v11 = *pv11;

	if (v00 == v01) {
		return (v10 < v11);
	}

	return (v00 < v01);
}


#endif