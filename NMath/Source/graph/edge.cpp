#include <iostream>
#include <cassert>

#include <nmath/graph/vert.hpp> // gr/vert.hpp.in
#include <nmath/graph/edge_data.hpp> // gr/edge.hpp.in

#include <nmath/graph/edge.hpp> // gr/edge.hpp.in

typedef nmath::graph::edge THIS;


THIS::edge(nmath::graph::VERT_S const & v0, nmath::graph::VERT_S const & v1, nmath::graph::EDGE_DATA_S const & data) :
	_M_v0(v0),
	_M_v1(v1),
	_M_data(data)
{
//	std::cout << "edge ctor" << std::endl;
	assert(v0);
	assert(v1);
}
bool			THIS::enabled() const
{
	//assert(!_M_v0.expired());
	if(_M_v0.expired()) return false;

	if(_M_v1.expired()) return false;

	auto const & v0 = _M_v0.lock();
	auto const & v1 = _M_v1.lock();
	
	if(!v0->enabled()) return false;

	if(!v1->enabled()) return false;
	
	if(!_M_data->_M_enabled) return false;

	return true;
}
bool			THIS::operator<(nmath::graph::edge const & e) const
{
	nmath::graph::VERT_S pv00 = _M_v0.lock();
	nmath::graph::VERT_S pv01 = e._M_v0.lock();
	nmath::graph::VERT_S pv10 = _M_v1.lock();
	nmath::graph::VERT_S pv11 = e._M_v1.lock();
	nmath::graph::vert & v00 = *pv00;
	nmath::graph::vert & v01 = *pv01;
	nmath::graph::vert & v10 = *pv10;
	nmath::graph::vert & v11 = *pv11;
	
	if(v00 == v01) {
		return (v10 < v11);
	}

	return (v00 < v01);
}
bool			THIS::operator==(nmath::graph::edge const & e) const
{
	nmath::graph::VERT_S pv00 = _M_v0.lock();
	nmath::graph::VERT_S pv01 = e._M_v0.lock();
	nmath::graph::VERT_S pv10 = _M_v1.lock();
	nmath::graph::VERT_S pv11 = e._M_v1.lock();
	nmath::graph::vert & v00 = *pv00;
	nmath::graph::vert & v01 = *pv01;
	nmath::graph::vert & v10 = *pv10;
	nmath::graph::vert & v11 = *pv11;

	return (v00 == v01) && (v10 == v11);
}



