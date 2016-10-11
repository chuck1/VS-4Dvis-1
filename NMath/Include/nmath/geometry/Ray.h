#ifndef NMATH_GEOMETRY_RAY
#define NMATH_GEOMETRY_RAY

#include <nmath/linalg/Vec.h>

namespace nmath {
	namespace geometry {

		class RayBase
		{
		public:
			virtual void serialize(nmath::util::Buffer & c) const = 0;
			virtual void deserialize(nmath::util::Buffer & c) = 0;
		};

		template<unsigned int M>
		class Ray: public RayBase
		{
		public:
			nmath::linalg::Vec<M> x(double k)
			{
				return p + v*k;
			}

			virtual void serialize(nmath::util::Buffer & c) const
			{
				//nmath::util::write(c, p);
				//c.write<nmath::linalg::Vec<M>>(p);
				c.write((void*)&p, sizeof(nmath::linalg::Vec<M>));
			}
			virtual void deserialize(nmath::util::Buffer & c)
			{

			}


		public:
			nmath::linalg::Vec<M> p;
			nmath::linalg::Vec<M> v;
		};
	}
}

#endif


