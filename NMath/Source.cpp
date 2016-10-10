
#include <iostream>
#include <cstdio>
#include <iomanip>

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
			os << std::setw(5) << std::setprecision(2) << std::fixed << m(i, j) << " ";
		}
		os << std::endl;
	}
	return os;
}

void test_gauss_elim()
{
	nmath::Mat<3, 6> m;
	
	m(0, 0) = 1;
	m(0, 1) = 0;
	m(0, 2) =-3;
	m(0, 3) = 0;
	m(0, 4) = 2;
	m(0, 5) =-8;

	m(1, 0) = 0;
	m(1, 1) = 1;
	m(1, 2) = 5;
	m(1, 3) = 0;
	m(1, 4) =-1;
	m(1, 5) = 4;

	m(2, 0) = 0;
	m(2, 1) = 0;
	m(2, 2) = 0;
	m(2, 3) = 1;
	m(2, 4) = 7;
	m(2, 5) =-9;

	auto m1 = m.transpose();

	//std::cout << m << std::endl;
	
	//nmath::gaussianElimination(m);

	//std::cout << m << std::endl;
	
	////////////

	

	auto m2 = nmath::SMat<6>::Identity();
	
	std::cout << m1 << std::endl;
	//std::cout << m2 << std::endl;
	
	nmath::gaussianElimination(m1, m2);
	
	std::cout << m1.transpose() << std::endl;
	
	std::cout << m2.transpose() << std::endl;

	std::cout << "dot" << std::endl;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 3; j < 6; ++j)
			std::cout << nmath::linalg::dot(nmath::row(m, i), nmath::column(m2.transpose(), j)) << std::endl;
	}
	std::cout << "dot" << std::endl;
}
void test_array()
{
	auto arr = std::make_shared<nmath::util::Array<double>>();

	auto d = arr->push_back(0);

	d->ref() = 1;

}

class ArrayIndirectTestClass
{
public:
	std::vector<unsigned int> v;
	unsigned int size_byte() const
	{
		return v.size() * sizeof(unsigned int);
	}
	void serialize(char * c) const
	{
		auto l = size_byte();
		if (l == 0) return;
		memcpy(c, &v[0], l);
	}
};
template<unsigned int M>
void test_array_indirect()
{
	std::cout << "test_array_indirect" << std::endl;

	auto arr = std::make_shared < nmath::util::ArrayIndirect<nmath::geometry::Polytope<M>>>();

	std::cout << arr->size_buffer() << std::endl;
	arr->print();

	//ArrayIndirectTestClass c0;
	nmath::geometry::Polytope<M> p0;

	auto v0 = arr->push_back(p0);

	std::cout << arr->size_buffer() << std::endl;
	arr->print();

	//v0->ref().v.push_back(1);

	arr->refresh();

	std::cout << arr->size_buffer() << std::endl;
	arr->print();
}
void test_polytope()
{
	std::cout << "polytope" << std::endl;

	auto planes = std::make_shared<nmath::util::Array<nmath::geometry::Plane<4>>>();

	auto p = std::make_shared<nmath::geometry::Polytope<4>>();

	// hyperplanes

	/*p->_M_planes[0] = planes->push_back_index_ref(
		nmath::geometry::Plane<4>(nmath::linalg::Vec<4>::baseVec(0), 0),
		[&](unsigned int i){ p->_M_planes_ref[0] = i; },
		[&](){ return p->_M_planes_ref[0]; });*/

	// faces

	for (int j = 0; j < 4; ++j)
	{
		p->_M_faces[2 * j + 0]._M_plane.n = nmath::linalg::Vec<4>::baseVec(j);
		p->_M_faces[2 * j + 0]._M_plane.d = 1;
		p->_M_faces[2 * j + 0].calc_basis();
		p->_M_faces[2 * j + 0]._M_p = p->_M_faces[2 * j + 0]._M_plane.n;

		p->_M_faces[2 * j + 1]._M_plane.n = -nmath::linalg::Vec<4>::baseVec(j);
		p->_M_faces[2 * j + 1]._M_plane.d = 1;
		p->_M_faces[2 * j + 1].calc_basis();
		p->_M_faces[2 * j + 1]._M_p = p->_M_faces[2 * j + 1]._M_plane.n;

	}
	
	
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (i == j) continue;

			p->_M_faces[2*i + 0].AddHyperplaneIntersection(p->_M_faces[2 * j + 0]._M_plane);
			p->_M_faces[2*i + 0].AddHyperplaneIntersection(p->_M_faces[2 * j + 1]._M_plane);

			p->_M_faces[2*i + 1].AddHyperplaneIntersection(p->_M_faces[2 * j + 0]._M_plane);
			p->_M_faces[2*i + 1].AddHyperplaneIntersection(p->_M_faces[2 * j + 1]._M_plane);
		}
	}

	

	for (int i = 0; i < 8; ++i)
	{
		std::cout << "Face " << i << std::endl;
		std::cout << "  n" << std::endl;
		std::cout << p->_M_faces[i]._M_plane.n << std::endl;
		std::cout << "  A" << std::endl;
		std::cout << p->_M_faces[i]._M_A << std::endl;
		std::cout << "  inequalities" << std::endl;

		for (int j = 0; j < p->_M_faces[i]._M_inequalities.size(); ++j)
		{
			std::cout << "    a" << std::endl;
			std::cout << p->_M_faces[i]._M_inequalities[j]._M_a << std::endl;
			std::cout << "    d = " << p->_M_faces[i]._M_inequalities[j]._M_d << std::endl;
		}
	}

	// features
	// k = 0
	p->nmath::geometry::FeatureSet<4, 0>::_M_features[0] = std::make_shared<nmath::geometry::Feature<4, 0>>();

	// topology

	p->_M_topology = std::make_shared<nmath::geometry::topo::Graph<4>>();

	auto v0_0 = std::make_shared<nmath::geometry::topo::Vertex<4, 0>>(p->_M_topology, p->nmath::geometry::FeatureSet<4, 0>::_M_features[0]);
	auto v0_1 = std::make_shared<nmath::geometry::topo::Vertex<4, 0>>(p->_M_topology, p->nmath::geometry::FeatureSet<4, 0>::_M_features[1]);
	
	auto v1_0 = std::make_shared<nmath::geometry::topo::Vertex<4, 1>>(p->_M_topology, p->nmath::geometry::FeatureSet<4, 1>::_M_features[0]);

	nmath::graph::graph::add_edge<nmath::geometry::topo::VertexBase<4>>(*(p->_M_topology), v0_0, v1_0);
	nmath::graph::graph::add_edge<nmath::geometry::topo::VertexBase<4>>(*(p->_M_topology), v0_1, v1_0);

	std::cout << "graph size = " << p->_M_topology->vert_size() << std::endl;
	std::cout << std::endl;
}
void test_linalg()
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
}
void test_ray()
{
	std::cout << "test_ray" << std::endl;

	nmath::geometry::Ray<3> r;
	
	std::cout << ((long)&(r.p) - (long)&(r)) << std::endl;
	std::cout << ((long)&(r.v) - (long)&(r)) << std::endl;
	std::cout << sizeof(r) << std::endl;
}

void nmath::test()
{
	//test_gauss_elim();
	//test_array();
	//test_polytope();
	//test_ray();
	test_array_indirect<4>();

	getchar();
	exit(0);


	// graph
#if 0
	auto g = std::make_shared<nmath::geometry::topo::Graph<4>>();

	auto v0 = std::make_shared<nmath::geometry::topo::Vertex<4,0>>(g);
	auto v1 = std::make_shared<nmath::geometry::topo::Vertex<4,0>>(g);

	//g->add_edge(v0, v1);
	nmath::graph::graph::add_edge<nmath::geometry::topo::VertexBase<4>>(*g, v0, v1);

	std::cout << "graph" << std::endl;
	std::cout << g->vert_size() << std::endl;

	// data use
	std::cout << "PolytopePrimitive<4>   " << sizeof(nmath::geometry::PolytopePrimitive<4>) << std::endl;
#endif








	getchar();

	

	

}

