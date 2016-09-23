
#include <iostream>
#include <cstdio>

#include "Vec.h"
#include "VecFunctions.h"
#include "Mat.h"
#include "NMath.h"


template<int M>
std::ostream& operator<<(std::ostream& os, Vec<M> const & v)
{
	for (int i = 0; i < M; ++i) os << v(i) << " ";
	return os;
}

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

	getchar();
}

