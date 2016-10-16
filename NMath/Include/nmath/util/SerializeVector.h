#ifndef NMATH_UTIL_SERIALIZEVECTOR
#define NMATH_UTIL_SERIALIZEVECTOR

#include <nmath/util/Serializable.h>

namespace nmath {
	namespace util {

		template<typename T>
		void serialize(nmath::util::Buffer & c, std::vector<T> const & v)
		{
			// placeholder to write byte-size of vector block

			nmath::util::BlockSizeWriterScoped scoped_outer(c);

			unsigned int s = v.size();

			c.write(&s, sizeof(unsigned int));

			for (auto it = v.begin(); it != v.end(); ++it)
			{
				// placeholder
				nmath::util::BlockSizeWriterScoped scoped(c);
				
				(*it).serialize(c);
			}
		}

	}
}

#endif