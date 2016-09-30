<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3
#include <iostream>
#include <cassert>

#include <nmath/graph/container/vert.hpp>
#include <nmath/graph/vert.hpp> // gr/vert.hpp.in
#include <nmath/graph/pair.hpp> // gr/pair.hpp.in

#include <nmath/graph/iterator/vert_comp.hpp> // gr/iterator/vert_comp.hpp.in

typedef nmath::graph::iterator::vert_comp THIS;

THIS::vert_comp(nmath::graph::container::vert & container, THIS::iterator j, int c):
	_M_container(container),
	_M_j(j),
	_M_c(c)
{
	next();
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

		if(v->comp._M_c == _M_c) break;

		//std::cout << "next " << v->comp._M_visited << " " << v->comp._M_c << " != " << _M_c << std::endl;

		++_M_j;
	}
}
nmath::graph::iterator::vert_comp		THIS::operator++()
{
	++_M_j;
	next();
	return nmath::graph::iterator::vert_comp(_M_container, _M_j, _M_c);
}
nmath::graph::iterator::vert_comp		THIS::operator++(int)
{
	nmath::graph::iterator::vert_comp ret(_M_container, _M_j, _M_c);
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

bool				THIS::operator==(nmath::graph::iterator::vert_comp const & i)
{
	return (_M_j == i._M_j);
}
bool				THIS::operator!=(nmath::graph::iterator::vert_comp const & i)
{
	return !(_M_j == i._M_j);
}


<<<<<<< HEAD
>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3
=======
>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3






