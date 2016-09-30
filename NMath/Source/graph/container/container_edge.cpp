<<<<<<< HEAD
=======
#include <nmath/graph/vert.hpp>
#include <nmath/graph/edge.hpp> // gr/edge.hpp.in

#include <nmath/graph/container/edge.hpp> // gr/container/edge.hpp.in

typedef nmath::graph::container::edge THIS;

nmath::graph::CONT_EDGE::iterator	THIS::begin() const
{
	return _M_container.begin();
}
nmath::graph::CONT_EDGE::iterator	THIS::end() const
{
	return _M_container.end();
}

nmath::graph::CONT_EDGE::iterator	THIS::erase(nmath::graph::CONT_EDGE::iterator const & it)
{
	return _M_container.erase(it);
}

nmath::graph::CONT_EDGE::iterator	THIS::find(nmath::graph::VERT_S const & u) const
{
	for(auto it = begin(); it != end(); ++it) {
		nmath::graph::edge const & edge = *it;
		nmath::graph::VERT_S v = edge._M_v1.lock();
		if((*v) == (*u)) return it;
	}
	return end();
}

std::pair<typename nmath::graph::CONT_EDGE::iterator, bool>	THIS::insert(nmath::graph::edge const & e)
{
	return _M_container.insert(e);
}

nmath::graph::CONT_EDGE::size_type			THIS::size() const
{
	return _M_container.size();
}



>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3

