#include <cassert>
#include <iostream>

// gr/decl.hpp.in
#include <nmath/graph/iterator/vert_graph.hpp>
#include <nmath/graph/vert.hpp>


#include <nmath/graph/container/vert.hpp> // gr/container/vert.hpp.in

typedef nmath::graph::container::vert THIS;

THIS::iterator		THIS::begin()
{
	return _M_container.begin();
}
THIS::iterator		THIS::end()
{
	return _M_container.end();
}
THIS::iterator		THIS::find(nmath::graph::VERT_S const & v)
{
	return _M_container.find(v);
}
THIS::iterator		THIS::erase(THIS::iterator & i)
{
	nmath::graph::VERT_W w = *i;

	assert(!w.expired());
	
	auto ret = _M_container.erase(i);
	
	assert(w.expired());
	
	return ret;
}
unsigned int			THIS::size() const
{
	//auto s1 = _M_container.size();
	//auto s2 = std::distance(begin(), end());
	return _M_container.size();
}
nmath::graph::CONT_VERT::iterator		THIS::insert(
	nmath::graph::CONT_VERT::iterator const & i, nmath::graph::CONT_VERT::value_type & v)
{
	return _M_container.insert(i, v);
}


