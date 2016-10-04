#ifndef NMATH_MAT
#define NMATH_MAT

#include <cmath>
#include <cassert>
#include <exception>

#include <nmath/linalg/Vec.h>

namespace nmath {

	/**
	* many of the operations on a matrix were moved to global functions because they return or utilize matrices of M-1 or N-1 dimension.
	* Therefore, if these functions were in the body of the class, they would cause infinite recursion of class specialization until an error occurs.
	* The simpliest solution is to use global template functions which are far easier to specialize to avoid creating matricies of dimensions 0 or less.
	*/
	template<int M, int N>
	class Mat
	{
	public:
		Mat<M, N>()
		{
			for (int i = 0; i < M; ++i)
			{
				for (int j = 0; j < N; ++j)
				{
					operator()(i, j) = 0;
				}
			}
		}
		Mat<M, N>(Mat<M, N> const & m)
		{
			for (int i = 0; i < M; ++i)
			{
				for (int j = 0; j < N; ++j)
				{
					operator()(i, j) = m(i, j);
				}
			}
		}

		double const & operator()(int i, int j) const
		{
			assert(i<M);
			assert(j<N);
			if ((i >= M) || (j >= N)) throw std::exception();

			return _M_v[i*N + j];
		}
		double & operator()(int i, int j)
		{
			assert(i<M);
			assert(j<N);
			if ((i >= M) || (j >= N)) throw std::exception();

			return _M_v[i*N + j];
		}

		Mat<N, M> transpose()
		{
			Mat<N, M> ret;
			for (int i = 0; i < M; ++i)
			{
				for (int j = 0; j < N; ++j)
				{
					ret(j, i) = operator()(i, j);
				}
			}
			return ret;
		}

		template<int O>
		Mat<M, O> operator*(Mat<N, O> const & m)
		{
			Mat<M, O> ret;
			for (int i = 0; i < M; ++i)
			{
				for (int j = 0; j < O; ++j)
				{
					for (int k = 0; k < N; ++k)
					{
						ret(i, j) += operator()(i, k) * m(k, j);
					}
				}
			}
			return ret;
		}

		nmath::linalg::Vec<M> operator*(nmath::linalg::Vec<N> v)
		{
			nmath::linalg::Vec<M> ret;
			for (int i = 0; i < M; ++i)
			{
				for (int j = 0; j < N; ++j)
				{
					ret(i) += operator()(i, j) * v(j);
				}
			}
			return ret;
		}

		void swapRows(unsigned int i0, unsigned int i1)
		{
			for (int j = 0; j < N; ++j)
			{
				/*double x = operator()(i1, j);
				operator()(i1, j) = operator()(i0, j);
				operator()(i0, j) = x;*/
				std::swap(operator()(i0, j), operator()(i1, j));
			}
		}

	private:
		double _M_v[M*N];
	};

	template<int M>
	class SMat : public Mat<M, M>
	{
	public:
		static SMat<M> Identity()
		{
			SMat<M> ret;
			for (int i = 0; i < M; i++)
			{
				ret(i, i) = 1;
			}
			return ret;
		}
		SMat<M>(Mat<M, M> const & m) : Mat<M, M>(m) {}
		SMat<M>(){}
	};

}

#endif



