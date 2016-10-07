#ifndef NMATH_GEOMETRY_INEQUALITY
#define NMATH_GEOMETRY_INEQUALITY



namespace nmath {
	namespace geometry {

		template<unsigned int K>
		class Inequality
		{
		public:
			Inequality(){}
			Inequality(nmath::linalg::Vec<K> const & a, double d) :
				_M_a(a),
				_M_d(d)
			{}

			double d(nmath::linalg::Vec<K> const & s)
			{
				return nmath::linalg::dot(_M_a, s);
			}
			bool eval(nmath::linalg::Vec<K> const & s)
			{
				return (d(s) < _M_d);
			}

			nmath::linalg::Vec<K> _M_a;
			double _M_d;
		};

	}
}

#endif