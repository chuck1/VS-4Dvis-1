#ifndef NMATH_GEOMETRY_RAY
#define NMATH_GEOMETRY_RAY

<<<<<<< HEAD
=======
#include <nmath/util/Serializable.h>
>>>>>>> 268bf01e8f6c31479771525ac3872ff9050934a7
#include <nmath/linalg/Vec.h>

namespace nmath {
	namespace geometry {
<<<<<<< HEAD
		template<unsigned int M>
		class Ray
		{
		public:
			nmath::linalg::Vec<M> p;
			nmath::linalg::Vec<M> v;
=======

		/*class RayBase
		{
		public:
			virtual void serialize(nmath::util::Buffer & c) const = 0;
			virtual void deserialize(nmath::util::Buffer & c) = 0;
		};*/
		struct Colorf
		{
			nmath::linalg::Vec<3> c;
		};
		struct Material
		{
			struct Colorf emittance;
			struct Colorf reflectance;
		};
		template<unsigned int M>
		struct RayCastResult
		{
			bool hit;
			float k;
			struct Material mat;
			nmath::linalg::Vec<M> x;
			nmath::linalg::Vec<M> n;

			unsigned int polytope_i;
			unsigned int face_i;

			char message[128];
		};

		template<unsigned int M>
		class Ray//: public RayBase
		{
		public:
			nmath::linalg::Vec<M> x(double k)
			{
				return p + v*k;
			}

			//virtual void serialize(nmath::util::Buffer & c) const
			//{
			//	//nmath::util::write(c, p);
			//	//c.write<nmath::linalg::Vec<M>>(p);
			//	//c.write((void*)&p, sizeof(nmath::linalg::Vec<M>));
			//}
			//virtual void deserialize(nmath::util::Buffer & c)
			//{

			//}


		public:
			nmath::linalg::Vec<M> p;
			nmath::linalg::Vec<M> v;

			nmath::linalg::Vec<3> color;

			RayCastResult<M>	res;
>>>>>>> 268bf01e8f6c31479771525ac3872ff9050934a7
		};
	}
}

#endif


