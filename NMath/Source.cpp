
#include <iostream>
#include <cstdio>

#include <nmath/Vec.h>
#include <nmath/VecFunctions.h>
#include <nmath/Mat.h>
#include <nmath/NMath.h>

#include <nmath/graph/graph.hpp>

template<int M>
std::ostream& operator<<(std::ostream& os, Vec<M> const & v)
{
	for (int i = 0; i < M; ++i) os << v(i) << " ";
	return os;
}

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
{
	Vec<5> a = Vec<5>::baseVec(0);
	Vec<5> b = Vec<5>::baseVec(1);
	Vec<5> c = Vec<5>::baseVec(2);
	Vec<5> d = Vec<5>::baseVec(3);

	auto e = normal<5>(a, b, c, d);

	auto m = SMat<5>::Identity();

	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << c << std::endl;
	std::cout << d << std::endl;
	std::cout << e << std::endl;

	std::cout << det(m) << std::endl;


	// graph

	auto g = std::make_shared<nmath::graph::Graph>();

	auto v0 = std::make_shared<Vertex>(g);
	auto v1 = std::make_shared<Vertex>(g);

	g->add_edge(v0, v1);

	std::cout << "graph" << std::endl;
	std::cout << g->vert_size() << std::endl;

	getchar();
}

