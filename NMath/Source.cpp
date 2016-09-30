
#include <iostream>
#include <cstdio>

#include <nmath/linalg/Vec.h>
#include <nmath/linalg/VecFunctions.h>
#include <nmath/linalg/Mat.h>
#include <nmath/linalg/NMath.h>
<<<<<<< HEAD
#include <nmath/geometry/Polytope.h>
#include <nmath/geometry/GraphTopology.h>
#include <nmath/vclip/Vclip.h>

#include <nmath/test.h>
#include <nmath/graph/graph.hpp>
#include <nmath/graph/container/edge.hpp>
#include <nmath/graph/GraphFunction.h>
=======

#include <nmath/graph/graph.hpp>
>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3

template<int M>
std::ostream& operator<<(std::ostream& os, nmath::linalg::Vec<M> const & v)
{
	for (int i = 0; i < M; ++i) os << v(i) << " ";
	return os;
}

<<<<<<< HEAD


void nmath::test()
=======
class Vertex : public nmath::graph::vert
{
public:
	Vertex(nmath::graph::GRAPH_S g):
		nmath::graph::vert(g)
	{}
	virtual bool		operator==(vert const & v)
	{
		Vertex const * v1 = dynamic_cast<Vertex const *>(&v);
		return (v1->d == d) && (v1->i == i);
	}
	virtual bool		operator<(vert const & v)
	{
		Vertex const * v1 = dynamic_cast<Vertex const *>(&v);
		if (v1->d == d)
		{
			return v1->i < i;
		}
		return v1->d < d;
	}

	int d;
	int i;
};

void NMath::test()
>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3
{
	nmath::linalg::Vec<5> a = nmath::linalg::Vec<5>::baseVec(0);
	nmath::linalg::Vec<5> b = nmath::linalg::Vec<5>::baseVec(1);
	nmath::linalg::Vec<5> c = nmath::linalg::Vec<5>::baseVec(2);
	nmath::linalg::Vec<5> d = nmath::linalg::Vec<5>::baseVec(3);

	auto e = nmath::linalg::normal<5>(a, b, c, d);

	auto m = nmath::SMat<5>::Identity();

	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << c << std::endl;
	std::cout << d << std::endl;
	std::cout << e << std::endl;

	std::cout << det(m) << std::endl;


	// graph
<<<<<<< HEAD
#if 1
	auto g = std::make_shared<nmath::geometry::topo::Graph>();

	auto v0 = std::make_shared<nmath::geometry::topo::Vertex>(g);
	auto v1 = std::make_shared<nmath::geometry::topo::Vertex>(g);

	//g->add_edge(v0, v1);
	nmath::graph::graph::add_edge(*g, v0, v1);
=======

	auto g = std::make_shared<nmath::graph::Graph>();

	auto v0 = std::make_shared<Vertex>(g);
	auto v1 = std::make_shared<Vertex>(g);

	g->add_edge(v0, v1);
>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3

	std::cout << "graph" << std::endl;
	std::cout << g->vert_size() << std::endl;

<<<<<<< HEAD
	// data use
	std::cout << "PolytopePrimitive<4>   " << sizeof(nmath::geometry::PolytopePrimitive<4>) << std::endl;
#endif
=======
>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3
	getchar();
}

