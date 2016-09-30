#ifndef NMATH_VCLIP_VCLIP
#define NMATH_VCLIP_VCLIP

<<<<<<< HEAD
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
=======
#include <nmath/graph/decl.hpp>

namespace nmath {
	namespace vclip {
		class Vclip
		{

			// topology graphs
			std::vector<nmath::graph::GRAPH_S> _M_topology;
>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3
		};
	}
}

#endif
<<<<<<< HEAD




=======
>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3
