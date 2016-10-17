#ifndef NMATH_UTIL_UTIL
#define NMATH_UTIL_UTIL

#define NMATH_UTIL_UTIL_DEBUG (0)

namespace nmath
{
	namespace util
	{

		template<typename WORD>
		inline WORD checksum(char const * buf, unsigned int len)
		{
			if (NMATH_UTIL_UTIL_DEBUG) printf("checksum\n");

			char const * end = buf + len;

			WORD ret;

			ret = *((WORD*)buf);

			if (NMATH_UTIL_UTIL_DEBUG) printf("pointer: %16i ret:%16u\n", end - buf, ret);

			buf += sizeof(WORD);

			if (NMATH_UTIL_UTIL_DEBUG) printf("pointer: %16i ret:%16u\n", end - buf, ret);

			while (buf <= (end - sizeof(WORD)))
			{
				if (NMATH_UTIL_UTIL_DEBUG) printf("pointer: %16i ret:%16u\n", end - buf, ret);

				ret = ret ^ *((WORD*)buf);
				buf += sizeof(WORD);
			}

			if (NMATH_UTIL_UTIL_DEBUG) printf("pointer: %16i ret:%16u\n", end - buf, ret);

			return ret;
		}

		template<typename WORD>
		inline WORD checksum2(char const * buf, unsigned int len)
		{
			if (NMATH_UTIL_UTIL_DEBUG) printf("checksum\n");

			char const * end = buf + len;

			WORD ret;

			ret = *((WORD*)buf);

			if (NMATH_UTIL_UTIL_DEBUG) printf("pointer: %16i ret:%16u\n", end - buf, ret);

			buf += sizeof(WORD);

			if (NMATH_UTIL_UTIL_DEBUG) printf("pointer: %16i ret:%16u\n", end - buf, ret);

			while (buf <= (end - sizeof(WORD)))
			{
				if (NMATH_UTIL_UTIL_DEBUG) printf("pointer: %16i ret:%16u\n", end - buf, ret);

				ret = ret + *((WORD*)buf);
				buf += sizeof(WORD);
			}

			if (NMATH_UTIL_UTIL_DEBUG) printf("pointer: %16i ret:%16u\n", end - buf, ret);

			return ret;
		}
	}
}


#endif