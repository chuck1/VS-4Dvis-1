#ifndef NMATH_UTIL_SERIALIZABLE
#define NMATH_UTIL_SERIALIZABLE



namespace nmath {
	namespace util {

		class BufferSizeCounter;

		template<typename BUFFER, typename T>
		void write(BUFFER & c, T const * t)
		{
			memcpy(c, t, sizeof(T));
			c += sizeof(T);
		}
		template<typename T>
		void write(BufferSizeCounter & c, T const * t)
		{
			c += sizeof(T);
		}

		class BufferSizeCounter
		{
		public:
			BufferSizeCounter() :_M_s(0){}

			unsigned int operator-(BufferSizeCounter const &)
			{
				return 0;
			}

			void operator +=(unsigned int s)
			{
				_M_s += s;
			}
			unsigned int _M_s;
		};

	}
}



#endif