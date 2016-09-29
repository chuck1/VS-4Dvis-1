
#include <iostream>
#include <cstdio>

#include <nmath/linalg/Vec.h>
#include <nmath/linalg/VecFunctions.h>
#include <nmath/linalg/Mat.h>
#include <nmath/linalg/NMath.h>

#include <nmath/graph/graph.hpp>
#include <nmath/graph/container/edge.hpp>

template<int M>
std::ostream& operator<<(std::ostream& os, nmath::linalg::Vec<M> const & v)
{
	for (int i = 0; i < M; ++i) os << v(i) << " ";
	return os;
}

class Vertex : public nmath::graph::Vert<Vertex>
{
public:
	typedef nmath::graph::Vert<Vertex> BASE;

	Vertex(BASE::G_S g) :
		BASE(g, std::make_shared<BASE::ECONT>())
	{}
	virtual bool		operator==(BASE const & v)
	{
		Vertex const * v1 = dynamic_cast<Vertex const *>(&v);
		return (v1->d == d) && (v1->i == i);
	}
	virtual bool		operator<(BASE const & v)
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

	auto g = std::make_shared<nmath::graph::Graph<Vertex>>();

	auto v0 = std::make_shared<Vertex>(g);
	auto v1 = std::make_shared<Vertex>(g);

	g->add_edge(v0, v1);

	std::cout << "graph" << std::endl;
	std::cout << g->vert_size() << std::endl;

	getchar();
}

