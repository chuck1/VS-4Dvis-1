


#include <nmath/util/Array.h>
#include <nmath/linalg/Vec.h>



namespace nspace {
	namespace actor {

		class Base
		{
		public:
			virtual ~Base(){}
		};

		class RigidBodyBase: public nspace::actor::Base
		{
		};

		template<int N>
		class RigidBody : RigidBodyBase
		{
		public:
			typedef std::shared_ptr<nmath::util::ArrayRef< nmath::linalg::Vec<N> > > VECTOR;
			
			VECTOR _M_ref_p;
		};

	}
}
