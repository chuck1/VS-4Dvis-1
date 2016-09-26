#include <iostream>
#include <cassert>

#include <nmath/graph/container/vert.hpp>
#include <nmath/graph/vert.hpp>
#include <nmath/graph/pair.hpp>

#include <nmath/graph/iterator/vert_graph_all.hpp>

typedef nmath::graph::iterator::vert_graph_all THIS;

THIS::vert_graph_all(nmath::graph::container::vert & container, THIS::iterator j) :
	_M_container(container),
	_M_j(j)
{
	next();
}
THIS::vert_graph_all(nmath::graph::container::vert & container, THIS::iterator j, nmath::graph::VERT_FUNC func) :
	_M_container(container),
	_M_j(j),
	_M_func(func)
{
	next();
}
THIS				THIS::operator=(THIS const & i)
{
	_M_container = i._M_container;
	_M_j = i._M_j;
	return *this;
}

void				THIS::next()
{
	while(true) {
		if(_M_j == _M_container.end()) break;
		
		graph::VERT_S const & v = *_M_j;

		assert(v);
		
		if(_M_func) {
			if(!_M_func(v)) {
				++_M_j;
				continue;
			}
		}

		break;
	}
}
nmath::graph::iterator::vert_graph_all		THIS::operator++()
{
	++_M_j;
	next();
	return graph::iterator::vert_graph_all(_M_container, _M_j);
}
nmath::graph::iterator::vert_graph_all		THIS::operator++(int)
{
	graph::iterator::vert_graph_all ret(_M_container, _M_j);
	operator++();
	return ret;
}

THIS::reference			THIS::operator*()
{
	return *_M_j;
}
THIS::value_type const *	THIS::operator->()
{
	return _M_j.operator->();
}

bool				THIS::operator==(nmath::graph::iterator::vert_graph_all const & i)
{
	return (_M_j == i._M_j);
}
bool				THIS::operator!=(nmath::graph::iterator::vert_graph_all const & i)
{
	return !(_M_j == i._M_j);
}








