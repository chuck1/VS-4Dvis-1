
#include <iostream>
#include <cstdio>

#include <nmath/linalg/Vec.h>
#include <nmath/linalg/VecFunctions.h>
#include <nmath/linalg/Mat.h>
#include <nmath/linalg/NMath.h>
#include <nmath/geometry/Polytope.h>
#include <nmath/geometry/GraphTopology.h>
#include <nmath/vclip/Vclip.h>

#include <nmath/test.h>
#include <nmath/graph/graph.hpp>
#include <nmath/graph/container/edge.hpp>
#include <nmath/graph/GraphFunction.h>

template<int M>
std::ostream& operator<<(std::ostream& os, nmath::linalg::Vec<M> const & v)
{
	for (int i = 0; i < M; ++i) os << v(i) << " ";
	return os;
}

template<int M, int N>
std::ostream& operator<<(std::ostream& os, nmath::Mat<M,N> const & m)
{
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			os << m(i,j) << " ";
		}
		os << std::endl;
	}
	return os;
}

void test_gauss_elim()
{
	nmath::Mat<3, 5> m;
	

	m(0, 0) = 7;
	m(0, 1) = 1;
	m(0, 2) = 1;
	
	m(1, 1) = 1;
	m(1, 2) = 2;
	
	m(2, 0) = 1;
	m(2, 1) = 0;
	m(2, 2) = 4;

	auto m1 = m.transpose();

	std::cout << m << std::endl;
	
	nmath::gaussianElimination(m);

	std::cout << m << std::endl;

	std::cout << m1 << std::endl;
	nmath::gaussianElimination(m1);
	std::cout << m1 << std::endl;
}

void nmath::test()
{
	test_gauss_elim();


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
#if 1
	auto g = std::make_shared<nmath::geometry::topo::Graph>();

	auto v0 = std::make_shared<nmath::geometry::topo::Vertex>(g);
	auto v1 = std::make_shared<nmath::geometry::topo::Vertex>(g);

	//g->add_edge(v0, v1);
	nmath::graph::graph::add_edge(*g, v0, v1);

	std::cout << "graph" << std::endl;
	std::cout << g->vert_size() << std::endl;

	// data use
	std::cout << "PolytopePrimitive<4>   " << sizeof(nmath::geometry::PolytopePrimitive<4>) << std::endl;
#endif








	getchar();

	

	

}

