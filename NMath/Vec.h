
#ifndef NMATH_VEC
#define NMATH_VEC


class Vector
{
public:
	static Vector baseVector(int n, int i)
	{
		Vector ret(n);
		ret(i) = 1;
		return ret;
	}

	Vector() :_M_n(0), _M_v(0){}
	Vector(unsigned int n) : _M_n(n)
	{
		_M_v = new double[_M_n];
		for (int i = 0; i < _M_n; ++i) _M_v[i] = 0;
	}
	void resize(int n)
	{

	}
	void operator=(Vector const & v)
	{
		for (int i = 0; i < _M_n; ++i)
		{
			operator()(i) = v(i);
		}
	}
	Vector operator-(Vector const & b)
	{
		Vector c(_M_n);
		for (int i = 0; i < _M_n; ++i)
		{
			c._M_v[i] = _M_v[i] - b._M_v[i];
		}
		return c;
	}
	void operator-=(Vector const & b)
	{
		for (int i = 0; i < _M_n; ++i)
		{
			_M_v[i] -= b._M_v[i];
		}
	}
	void operator+=(Vector const & b)
	{
		for (int i = 0; i < _M_n; ++i)
		{
			_M_v[i] += b._M_v[i];
		}
	}
	Vector operator*(int const & b)
	{
		Vector c(_M_n);
		for (int i = 0; i < _M_n; ++i)
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
		if (i >= _M_n) throw std::exception("index out of range");

		return _M_v[i];
	}

	unsigned int _M_n;
	double* _M_v;
};

template<typename... T>
int function(T... t){ return 0; }


int function(int & i, Vector *vectors, Vector vector)
{
	vectors[i] = vector;
	--i;
	return 0;
}

template<int N, typename... Args>
Vector normal(Args... args)
{
	Vector *vectors = new Vector[N-1];

	int i = N-2;
	
	function(function(i, vectors, args)...);

	Vector ret(N);

	Mat m0(N - 1, N);
	for (int i = 0; i < N - 1; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			vectors[i].resize(N);
			m0(i, j) = vectors[i](j);
		}
	}

	for (int i = 0; i < N; ++i)
	{
		//SMat<N - 1> m1(*((Mat<N-1,N-1>*)m0.subMat1(i)));
		//*((Mat<N - 1, N - 1>*)m0.subMat1(i))
		Mat m2(m0.subMat1(i));
		SMat m1(m2);

		ret += Vector::baseVector(N,i) * pow(-1, i) * m1.det();
	}

	return ret;
}



#endif
