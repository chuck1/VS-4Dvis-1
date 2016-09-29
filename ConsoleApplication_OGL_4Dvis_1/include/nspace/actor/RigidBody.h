
#include <nspace/util/Array.h>

#include <nmath/linalg/Vec.h>

namespace nspace {
	namespace actor {

		template<int N>
		class RigidBody
		{
		public:
			typedef std::shared_ptr<nspace::util::ArrayRef< nmath::linalg::Vec<N> > > VECTOR;
			
			VECTOR _M_ref_p;
		};

	}
}
