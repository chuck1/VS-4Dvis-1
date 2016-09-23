
#include "Mat.h"

template<int M,int N>
void subMat0(Mat<M,N> const & m, int i0)
{
	Mat ret(_M_m - 1, _M_n);

	for (int i = 0, a = 0; i < _M_m; ++i)
	{
		if (i == i0) continue;

		for (int j = 0, b = 0; j < _M_n; ++j)
		{
			ret(a, b) = operator()(i, j);

			++b;
		}

		++a;
	}
}
template<int M, int N>
Mat<M, N - 1> subMat1(Mat<M, N> const & m, int j0)
{
	Mat<M, N - 1> ret;

	for (int i = 0, a = 0; i < M; ++i)
	{
		for (int j = 0, b = 0; j < N; ++j)
		{
			if (j == j0) continue;

			ret(a, b) = m(i, j);

			++b;
		}
		++a;
	}

	return ret;
}
template<int M, int N>
Mat<M - 1, N - 1> subMat(Mat<M, N> const & m, int i0, int j0)
{
	Mat<M - 1, N - 1> ret;

	for (int i = 0, a = 0; i < N; ++i)
	{
		if (i == i0) continue;

		for (int j = 0, b = 0; j < M; ++j)
		{
			if (j == j0) continue;

			ret(a, b) = m(i, j);

			++b;
		}
		++a;
	}

	return ret;
}

template<int M>
SMat<M-1> subSMat(SMat<M> const & m, int i, int j)
{
	Mat<M-1,M-1> ret = subMat(m, i, j);

	SMat<M - 1> ret1(ret);

	return ret1;
}

template<int M>
double det(SMat<M> const & m)
{
	double ret = 0;

	for (int i = 0; i < M; ++i)
	{
		ret += m(0, i) * pow(-1, i) * det(subSMat(m, 0, i));
	}

	return ret;
}

template<>
double det(SMat<1> const & m)
{
	return m(0,0);
}




