
<<<<<<< HEAD
<<<<<<< HEAD
#include <nmath/util/Array.h>
=======
#include <nspace/util/Array.h>
>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3
=======
#include <nspace/util/Array.h>
>>>>>>> 2c62763c134a8484205fd6547a872d54976002a3

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
