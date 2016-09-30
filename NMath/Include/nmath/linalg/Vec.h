
#ifndef NMATH_VEC
#define NMATH_VEC

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
			Vec<M>(unsigned int n) : _M_n(n)
			{
				_M_v = new double[_M_n];
				for (int i = 0; i < _M_n; ++i) _M_v[i] = 0;
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
				Vec c(_M_n);
				for (int i = 0; i < _M_n; ++i)
				{
					c._M_v[i] = _M_v[i] - b._M_v[i];
				}
				return c;
			}
			void operator-=(Vec const & b)
			{
				for (int i = 0; i < _M_n; ++i)
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
				if (i >= M) throw std::exception("index out of range");

				return _M_v[i];
			}

			double _M_v[M];
		};
	}
}


#endif
