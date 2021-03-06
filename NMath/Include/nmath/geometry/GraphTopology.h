#ifndef NMATH_GEOMETRY_GRAPHTOPOLOGY
#define NMATH_GEOMETRY_GRAPHTOPOLOGY

<<<<<<< HEAD

#include <nmath/graph/graph.hpp>
=======
#include <memory>

#include <nmath/vclip/Feature.h>

#include <nmath/graph/graph.hpp>
#include <nmath/graph/container/edge.hpp>
>>>>>>> 268bf01e8f6c31479771525ac3872ff9050934a7

namespace nmath {
	namespace geometry {
		namespace topo {
<<<<<<< HEAD

			class Vertex : public nmath::graph::Vert<Vertex>
			{
			public:
				typedef nmath::graph::Vert<Vertex> BASE;

				Vertex(BASE::G_S g) :
					BASE(g, std::make_shared<BASE::ECONT>())
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
=======
			template<int M>
			class VertexBase : public nmath::graph::Vert<VertexBase<M>>
			{
			public:
				typedef nmath::graph::Vert<VertexBase<M>> BASE;

				VertexBase<M>(typename BASE::G_S g) :
					BASE(g, std::make_shared<nmath::graph::container::Edge<VertexBase<M>>>())
				{}

				virtual int k() const = 0;
				
				virtual std::shared_ptr<nmath::geometry::FeatureBase<M>> feature() const = 0;

			};
			template<int M, int K>
			class Vertex: public VertexBase<M>
			{
			public:
				typedef nmath::graph::Vert<VertexBase<M>> BASE;

				Vertex<M, K>(typename BASE::G_S g, std::shared_ptr<nmath::geometry::Feature<M, K>> f) :
					VertexBase<M>(g),
					_M_feature(f)
				{}


				virtual bool		operator==(VertexBase<M> const & v)
				{
					return (v.k() == k()) && (v.feature() == feature());
				}
				virtual bool		operator<(VertexBase<M> const & v)
				{
					if (v.k() == k())
					{
						return v.feature() < feature();
					}
					return v.k() < k();
				}

				virtual int k() const
				{
					return K;
				}
				virtual std::shared_ptr<nmath::geometry::FeatureBase<M>> feature() const
				{
					return _M_feature;
				}

				/* feature */
				std::shared_ptr<nmath::geometry::Feature<M, K>> _M_feature;
			};

			template<int M>
			class Graph : public nmath::graph::Graph<VertexBase<M>>
>>>>>>> 268bf01e8f6c31479771525ac3872ff9050934a7
			{

			};

		}
	}
}

<<<<<<< HEAD
#endif
=======
#endif
>>>>>>> 268bf01e8f6c31479771525ac3872ff9050934a7
