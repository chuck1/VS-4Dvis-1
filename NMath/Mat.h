#ifndef NMATH_MAT
#define NMATH_MAT

#include <cmath>
#include <cassert>
#include <exception>

class Mat
{
public:
	~Mat()
	{
		delete[] _M_v;
	}

	Mat(int m, int n):
		_M_m(m), _M_n(n)
	{
		_M_v = new double[_M_m*_M_n];
		
		for (int i = 0; i < _M_m; ++i)
		{
			for (int j = 0; j < _M_n; ++j)
			{
				operator()(i, j) = 0;
			}
		}
	}
	Mat(Mat const & m):
		_M_m(m._M_m), _M_n(m._M_n)
	{
		_M_v = new double[_M_m*_M_n];
		//_M_v.resize(_M_m*_M_n);

		for (int i = 0; i < _M_m; ++i)
		{
			for (int j = 0; j < _M_n; ++j)
			{
				operator()(i, j) = m(i,j);
			}
		}
	}

	double const & operator()(int i, int j) const
	{
		if ((i >= _M_m) || (j >= _M_n)) throw std::exception("index out of range");

		return _M_v[i*_M_m+j];
	}
	double & operator()(int i, int j)
	{
		if ((i >= _M_m) || (j >= _M_n)) throw std::exception("index out of range");

		return _M_v[i*_M_m+j];
	}

	Mat subMat0(int i0)
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
	Mat subMat1(int j0)
	{
		Mat ret(_M_m, _M_n - 1);

		for (int i = 0, a = 0; i < _M_m; ++i)
		{
			for (int j = 0, b = 0; j < _M_n; ++j)
			{
				if (j == j0) continue;

				ret(a, b) = operator()(i, j);

				++b;
			}
			++a;
		}

		return ret;
	}
	Mat subMat(int i0, int j0)
	{
		Mat ret(_M_m - 1, _M_n - 1);

		for (int i = 0, a = 0; i < _M_m; ++i)
		{
			if (i == i0) continue;

			for (int j = 0, b = 0; j < _M_n; ++j)
			{
				if (j == j0) continue;

				ret(a, b) = operator()(i, j);

				++b;
			}
			++a;
		}

		return ret;
	}

	unsigned int _M_m;
	unsigned int _M_n;

private:
	double* _M_v;
};

class SMat: public Mat
{
public:
	SMat(Mat const & m) : Mat(m) {}

	SMat subSMat(int i, int j)
	{	
		Mat ret = subMat(i, j);

		SMat ret1(ret);

		return ret1;
	}
	
	virtual double det()
	{
		double ret = 0;

		for (int i = 0; i < _M_m; ++i)
		{
			ret += operator()(0, i) * pow(-1, i) * subSMat(0, i).det();
		}

		return ret;
	}
	
};

#endif