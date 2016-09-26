


#include <nmath/graph/layer.hpp>

typedef nmath::graph::layer THIS;

THIS::layer():
	_M_enabled(true)
{
}
bool		THIS::enabled() const
{
	return _M_enabled;
}


