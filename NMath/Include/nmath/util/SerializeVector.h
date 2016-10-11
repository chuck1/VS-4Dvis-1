#ifndef NMATH_UTIL_SERIALIZEVECTOR
#define NMATH_UTIL_SERIALIZEVECTOR

#include <nmath/util/Serializable.h>

namespace nmath {
	namespace util {

		template<typename T>
		void serialize(nmath::util::Buffer & c, std::vector<T> const & v)
		{
			// placeholder to write byte-size of vector block

			unsigned int d = c.pointer();

			c += sizeof(unsigned int);

			unsigned int s = v.size();

			c.write(&s, sizeof(unsigned int));

			for (auto it = v.begin(); it != v.end(); ++it)
			{
				// placeholder
				unsigned int c1 = c.pointer();
				c += sizeof(unsigned int);

				(*it).serialize(c);

				unsigned int s1 = c - c1;

				c -= s1;
				c.write((void*)&s1, sizeof(unsigned int));
				c += s1;
			}

			unsigned int sb = c - d;

			c -= sb;
			c.write(&sb, sizeof(unsigned int));
			c += sb;
		}

	}
}

#endif