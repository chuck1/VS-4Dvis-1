#ifndef NMATH_GEOMETRY_GRAPHTOPOLOGY
#define NMATH_GEOMETRY_GRAPHTOPOLOGY

#include <memory>

#include <nmath/graph/graph.hpp>
#include <nmath/graph/container/edge.hpp>

namespace nmath {
	namespace geometry {
		namespace topo {

			class Vertex : public nmath::graph::Vert<Vertex>
			{
			public:
				typedef nmath::graph::Vert<Vertex> BASE;

				Vertex(BASE::G_S g) :
					BASE(g, std::make_shared<nmath::graph::container::Edge<Vertex>>())
				{}
				virtual bool		operator==(Vertex const & v)
				{
					//Vertex const * v1 = dynamic_cast<Vertex const *>(&v);
					//return (v1->d == d) && (v1->i == i);
					return (v.d == d) && (v.i == i);
				}
				virtual bool		operator<(Vertex const & v)
				{
					//Vertex const * v1 = dynamic_cast<Vertex const *>(&v);
					/*if (v1->d == d)
					{
						return v1->i < i;
					}
					return v1->d < d;*/
					if (v.d == d)
					{
						return v.i < i;
					}
					return v.d < d;
				}

				int d;
				int i;
			};

			class Graph : public nmath::graph::Graph<Vertex>
			{

			};

		}
	}
}

#endif