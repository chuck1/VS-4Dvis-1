#ifndef NMATH_UTIL_BLOCKSIZEWRITERSCOPED
#define NMATH_UTIL_BLOCKSIZEWRITERSCOPED

#include <nmath/util/Serializable.h>

namespace nmath
{
	namespace util
	{
		class BlockSizeWriterScoped
		{
		public:
			BlockSizeWriterScoped(Buffer & nbuffer) : buffer(nbuffer)
			{
				c = buffer.pointer();
				buffer += sizeof(unsigned int);
			}
			~BlockSizeWriterScoped()
			{
				unsigned int s = buffer - c;

				//printf("block size: %4i\n", s);

				buffer -= s;
				buffer.write((char*)&s, sizeof(unsigned int));
				buffer += s - sizeof(unsigned int);
			}

			unsigned int c;
			Buffer & buffer;
		};
	}
}

#endif