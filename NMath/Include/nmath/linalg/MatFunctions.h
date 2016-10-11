#ifndef NMATH_LINALG_MATFUNCTION
#define NMATH_LINALG_MATFUNCTION

#include <algorithm>
#include <exception>

#include "Mat.h"
#include <nmath/linalg/Vec.h>

namespace nmath {

	template<int M, int N>
	Mat<M - 1, N> subMat0(Mat<M, N> const & m, int i0)
	{
		Mat<M - 1, N> ret;

		for (int i = 0, a = 0; i < M; ++i)
		{
			if (i == i0) continue;

			for (int j = 0, b = 0; j < N; ++j)
			{
				ret(a, b) = m(i, j);

				++b;
			}

			++a;
		}
		return ret;
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
	SMat<M - 1> subSMat(SMat<M> const & m, int i, int j)
	{
		Mat<M - 1, M - 1> ret = subMat(m, i, j);

		SMat<M - 1> ret1(ret);

		return ret1;
	}

	template<int M>
	float det(SMat<M> const & m)
	{
		double ret = 0;

		for (int i = 0; i < M; ++i)
		{
			ret += m(0, i) * pow(-1, i) * det(subSMat(m, 0, i));
		}

		return ret;
	}

	template<>
	inline float det(SMat<1> const & m)
	{
		return m(0, 0);
	}

	template<int M, int N>
	nmath::linalg::Vec<M> column(Mat<M, N> const & m, int j)
	{
		nmath::linalg::Vec<M> ret;
		for (int i = 0; i < M; ++i)
		{
			ret(i) = m(i, j);
		}
		return ret;
	}
	template<int M, int N>
	nmath::linalg::Vec<N> row(Mat<M, N> const & m, int i)
	{
		nmath::linalg::Vec<N> ret;
		for (int j = 0; j < N; ++j)
		{
			ret(j) = m(i, j);
		}
		return ret;
	}


	template<int M, int N>
	int argmax(Mat<M, N> & m, int k)
	{
		int i0 = k;
		double d0 = m(i0, k);

		for (int i = i0 + 1; i < M; ++i)
		{
			if (m(i, k)>d0)
			{
				d0 = m(i, k);
				i0 = i;
			}
		}

		return i0;
	}

	template<int M, int N>
	void subtractRow(Mat<M, N> & m, int i0, int i1, double f)
	{
		for (int j = 0; j < N; ++j)
		{
			m(i0, j) -= m(i1, j) * f;
		}
	}

	template<int M, int N>
	void multiplyRow(Mat<M, N> & m, int i, double f)
	{
		for (int j = 0; j < N; ++j)
		{
			m(i, j) *= f;
		}
	}

	template<int M, int N>
	void divideRow(Mat<M, N> & m, int i, double f)
	{
		for (int j = 0; j < N; ++j)
		{
			m(i, j) /= f;
		}
	}

	template<int M, int N>
	void gaussianElimination(Mat<M, N> & m)
	{
		for (unsigned int k = 0; k < std::min(M, N); ++k)
		{
			int i_max = argmax(m, k);
			
			if (m(i_max, k) == 0){
				//throw new std::exception();
				continue;
			}

			if (k != i_max) m.swapRows(k, i_max);

			// experimental
			// make first non-zero term of the row equal to 1
			//std::cout << "m(k,k)=" << m(k, k) << std::endl;

			for (int j = k + 1; j < N; ++j)
			{
				m(k, j) /= m(k, k);
			}
			m(k, k) = 1;

			// experimental
			// for each previous row
			for (int i = 0; i < k; ++i)
			{
				subtractRow(m, i, k, m(i, k));
			}


			for (int i = k + 1; i < M; ++i)
			{
				double f = m(i, k);

				for (int j = k + 1; j < N; ++j)
				{
					m(i, j) = m(i, j) - m(k, j) * f;
				}

				m(i, k) = 0;
			}
		}
	}

	template<unsigned int M, unsigned int N, int N1>
	void gaussianElimination(Mat<M, N> & m, Mat<M, N1> & m1)
	{
		for (unsigned int k = 0; k < std::min(M, N); ++k)
		{
			// fix negative
			for (int i = k; i < M; ++i)
			{
				if (m(i, k) < 0)
				{
					multiplyRow(m, i, -1);
				}
			}

			// swap
			int i_max = argmax(m, k);

			if (m(i_max, k) == 0) throw new std::exception();

			m.swapRows(k, i_max);
			m1.swapRows(k, i_max);

			// experimental
			// make first non-zero term of the row equal to 1

			double d = m(k, k);
			for (int j = k + 1; j < N; ++j)
			{
				m(k, j) /= d;
			}
			m(k, k) = 1;

			divideRow(m1, k, d);

			// experimental
			// for each previous row
			for (unsigned int i = 0; i < k; ++i)
			{
				subtractRow(m, i, k, m(i, k));

				subtractRow(m1, i, k, m(i, k));
			}
			

			// for each lower row
			for (unsigned int i = k + 1; i < M; ++i)
			{
				double f = m(i, k);

				for (unsigned int j = k + 1; j < N; ++j)
				{
					m(i, j) -= m(k, j) * f;
				}

				m(i, k) = 0;

				subtractRow(m1, i, k, f);
			}
		}
	}
}


#endif