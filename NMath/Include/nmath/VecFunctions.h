
#include "Vec.h"
#include "MatFunctions.h"

template<typename... T>
int function(T... t){ return 0; }

template<int M>
int function(int & i, Vec<M> *Vecs, Vec<M> Vec)
{
	Vecs[i] = Vec;
	--i;
	return 0;
}

template<int N, typename... Args>
Vec<N> normal(Args... args)
{
	Vec<N> *Vecs = new Vec<N>[N - 1];

	int i = N - 2;

	function(function(i, Vecs, args)...);

	Vec<N> ret;

	Mat<N - 1, N> m0;
	for (int i = 0; i < N - 1; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			Vecs[i].resize(N);
			m0(i, j) = Vecs[i](j);
		}
	}

	for (int i = 0; i < N; ++i)
	{
		SMat<N - 1> m1(subMat1(m0,i));
		//*((Mat<N - 1, N - 1>*)m0.subMat1(i))
		//Mat m2(m0.subMat1(i));
		//SMat m1(m2);

		ret += Vec<N>::baseVec(i) * pow(-1, i) * det(m1);
	}

	return ret;
}


