
#ifndef NMATH_VEC
#define NMATH_VEC

#include <limits>
#include <cmath>
#include <cassert>

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
			Vec operator+(Vec const & b)
			{
				Vec c;
				for (int i = 0; i < M; ++i)
				{
					c._M_v[i] = _M_v[i] + b._M_v[i];
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
			Vec operator-()
			{
				Vec<M> ret;
				for (int i = 0; i < M; ++i)
				{
					ret(i) = -operator()(i);
				}
				return ret;
			}
			Vec<M> operator*(float const & b)
			{
				Vec<M> c;
				for (int i = 0; i < M; ++i)
				{
					c(i) = operator()(i) * b;
				}
				return c;
			}
			
			float length() const
			{
				float d = 0;
				for (int i = 0; i < M; ++i)
				{
					d += operator()(i) * operator()(i);
				}
				return sqrt(d);
			}
			void normalize()
			{
				float d = length();

				assert(d > 0);

				for (int i = 0; i < M; ++i)
				{
					operator()(i) /= d;
				}
			}

			float const & operator()(int i) const
			{
				return _M_v[i];
			}
			float & operator()(int i)
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

			float _M_v[M];
		};
	}
}

#endif

