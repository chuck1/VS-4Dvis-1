#ifndef NMATH_GEOMETRY_INEQUALITY
#define NMATH_GEOMETRY_INEQUALITY



namespace nmath {
	namespace geometry {

		template<unsigned int K>
		class Inequality
		{
		public:
			Inequality(){}
			Inequality(nmath::linalg::Vec<K> const & a, float d) :
				_M_a(a),
				_M_d(d)
			{}

			float d(nmath::linalg::Vec<K> const & s)
			{
				return nmath::linalg::dot(_M_a, s);
			}
			bool eval(nmath::linalg::Vec<K> const & s)
			{
				return (d(s) < _M_d);
			}

			virtual void serialize(nmath::util::Buffer & c) const
			{
				c.write((char*)&_M_a, sizeof(nmath::linalg::Vec<K>));
				c.write((char*)&_M_d, sizeof(float));
			}
			virtual void deserialize(nmath::util::Buffer & c)
			{

			}

		public:
			nmath::linalg::Vec<K> _M_a;
			float _M_d;
		};

	}
}

#endif