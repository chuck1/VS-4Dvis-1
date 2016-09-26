#include <iostream>
#include <algorithm>
#include <cassert>

#include <nmath/graph/vert.hpp>
#include <nmath/graph/vert_comp.hpp>


bool nmath::graph::vert_comp::operator()(VERT_S const & np0, VERT_S const & np1)
{
	return (*np0) < (*np1);
}

