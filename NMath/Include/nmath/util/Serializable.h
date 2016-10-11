#ifndef NMATH_UTIL_SERIALIZABLE
#define NMATH_UTIL_SERIALIZABLE



namespace nmath {
	namespace util {

		class BufferChar;
		class BufferSizeCounter;

		/*template<typename T>
		void write(BufferChar & c, T const * t)
		{
			memcpy(c._M_c, t, sizeof(T));
			c._M_c += sizeof(T);
		}
		template<typename T>
		void write(BufferSizeCounter & c, T const * t)
		{
			c += sizeof(T);
		}*/

		class Buffer
		{
		public:
			Buffer() :_M_c(0)
			{
			}
			Buffer(char * c) : _M_c(c)
			{

			}
			Buffer(Buffer const & b) : _M_c(b._M_c)
			{

			}
			unsigned long pointer() const
			{
				return (unsigned long)_M_c;
			}
			unsigned long operator-(Buffer const & b)
			{
				return (pointer() - b.pointer());
			}
			unsigned long operator-(unsigned int const & b)
			{
				return (pointer() - b);
			}
			void operator +=(unsigned int s)
			{
				_M_c += s;
			}
			void operator -=(unsigned int s)
			{
				_M_c -= s;
			}

			virtual void write(void * src, unsigned int len) = 0;

			char * _M_c;
		};

		class BufferSizeCounter: public Buffer
		{
		public:
			virtual void write(void * src, unsigned int len)
			{
				operator+=(len);
			}
		};

		class BufferChar : public Buffer
		{
		public:
			BufferChar(char * c) : Buffer(c)
			{}

			virtual void write(void * src, unsigned int len)
			{
				memcpy(_M_c, src, len);
				_M_c += len;
			}
		};
	}
}



#endif