
#include <iostream>

#include "Vec.h"
#include "Mat.h"
#include "NMath.h"

std::ostream& operator<<(std::ostream& os, Vector const & v)
{
	for (int i = 0; i < v._M_n; ++i) os << v(i) << " ";
	return os;
}

void NMath::test()
{
	Vector a = Vector::baseVector(5,0);
	Vector b = Vector::baseVector(5,1);
	Vector c = Vector::baseVector(5,2);
	Vector d = Vector::baseVector(5,3);

	normal<5>(a, b, c, d);

	Mat mat(5,5);


}

