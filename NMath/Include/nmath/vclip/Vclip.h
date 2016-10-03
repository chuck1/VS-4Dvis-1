#ifndef NMATH_VCLIP_VCLIP
#define NMATH_VCLIP_VCLIP

#include <memory>

#include <nmath/geometry/GraphTopology.h>
#include <nmath/geometry/Polytope.h>

namespace nmath {
	namespace vclip {
		/**
		* working class for the M-dimensinal VClip algorithm
		*/
		template<unsigned int M>
		class Vclip
		{
		public:
			/**
			* a vertex of the topology graph for shape 0
			*/
			std::shared_ptr<nmath::geometry::topo::Vertex> _M_v0;
			/**
			* a vertex of the topology graph for shape 1
			*/
			std::shared_ptr<nmath::geometry::topo::Vertex> _M_v1;

			std::shared_ptr<nmath::geometry::Polytope<M>> _M_p0;
			std::shared_ptr<nmath::geometry::Polytope<M>> _M_p1;
		};
	}
}

#endif

