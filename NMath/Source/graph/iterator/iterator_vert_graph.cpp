<<<<<<< HEAD
=======
#include <iostream>
#include <cassert>

#include <nmath/graph/container/vert.hpp>
#include <nmath/graph/vert.hpp> // gr/vert.hpp.in
#include <nmath/graph/pair.hpp> // gr/pair.hpp.in

#include <nmath/graph/iterator/vert_graph.hpp> // gr/iterator/vert_graph.hpp.in

typedef nmath::graph::iterator::vert_graph THIS;

THIS::vert_graph(nmath::graph::container::vert & container, THIS::iterator j):
	_M_container(container),
	_M_j(j)
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
		
		nmath::graph::VERT_S const & v = *_M_j;

		assert(v);

		if(!v->enabled()) {
			++_M_j;
			continue;
		}

		break;
	}
}
nmath::graph::iterator::vert_graph		THIS::operator++()
{
	++_M_j;
	next();
	return nmath::graph::iterator::vert_graph(_M_container, _M_j);
}
nmath::graph::iterator::vert_graph		THIS::operator++(int)
{
	nmath::graph::iterator::vert_graph ret(_M_container, _M_j);
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

bool				THIS::operator==(nmath::graph::iterator::vert_graph const & i)
{
	return (_M_j == i._M_j);
}
bool				THIS::operator!=(nmath::graph::iterator::vert_graph const & i)
{
	return !(_M_j == i._M_j);
}



>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3





