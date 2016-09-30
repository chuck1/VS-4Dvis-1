#ifndef NMATH_MAT
#define NMATH_MAT

#include <cmath>
#include <cassert>
#include <exception>

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
			if ((i >= M) || (j >= N)) throw std::exception();//"index out of range");

			return _M_v[i*M + j];
		}
		double & operator()(int i, int j)
		{
			if ((i >= M) || (j >= N)) throw std::exception();//"index out of range");

			return _M_v[i*M + j];
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



