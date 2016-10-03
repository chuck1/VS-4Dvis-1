
#ifndef NMATH_VEC
#define NMATH_VEC

#include <limits>

namespace nmath {
	namespace linalg {

		template<int M>
		class Vec
		{
		public:
			static Vec<M> baseVec(int i)
			{
				Vec<M> ret;
				ret(i) = 1;
				return ret;
			}

			Vec<M>()
			{
				for (int i = 0; i < M; ++i) operator()(i) = 0;
			}
			void resize(int n)
			{

			}
			void operator=(Vec const & v)
			{
				for (int i = 0; i < M; ++i)
				{
					operator()(i) = v(i);
				}
			}
			Vec operator-(Vec const & b)
			{
				Vec c;
				for (int i = 0; i < M; ++i)
				{
					c._M_v[i] = _M_v[i] - b._M_v[i];
				}
				return c;
			}
			void operator-=(Vec const & b)
			{
				for (int i = 0; i < M; ++i)
				{
					_M_v[i] -= b._M_v[i];
				}
			}
			void operator+=(Vec const & b)
			{
				for (int i = 0; i < M; ++i)
				{
					_M_v[i] += b._M_v[i];
				}
			}
			Vec<M> operator*(int const & b)
			{
				Vec<M> c;
				for (int i = 0; i < M; ++i)
				{
					c(i) = operator()(i) * b;
				}
				return c;
			}
			double const & operator()(int i) const
			{
				return _M_v[i];
			}
			double & operator()(int i)
			{
				if (i >= M) throw std::exception();//"index out of range");

				return _M_v[i];
			}

			Vec<M> abs() const
			{
				Vec<M> ret;
				for (int i = 0; i < M; ++i)
				{
					ret(i) = ::abs(operator()(i));
				}
			}
			int argmax() const
			{
				double d = operator()(0);
				int i0 = 0;

				for (int i = 1; i < M; ++i)
				{
					double x = operator()(i);
					if (x > d)
					{
						d = x;
						i0 = i;
					}
				}
				return i0;
			}

			double _M_v[M];
		};
	}
}


#endif
