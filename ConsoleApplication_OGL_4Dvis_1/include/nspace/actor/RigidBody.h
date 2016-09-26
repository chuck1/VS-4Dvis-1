
#include <nspace/util/Array.h>

#include <nmath/linalg/Vec.h>

namespace nspace {
	namespace actor {
		template<int N>
		class RigidBody
		{
		public:
			static const int N_E = N*(N - 1) / 2;

			typedef std::shared_ptr<nspace::util::ArrayRef< nmath::linalg::Vec<N> > > VECTOR;
			typedef std::shared_ptr<nspace::util::ArrayRef< nmath::linalg::Vec<N_E> > > VECTOR_E;

			VECTOR _M_ref_p;
		};
	}
}
