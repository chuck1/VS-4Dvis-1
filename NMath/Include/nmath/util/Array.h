
#include <iomanip>
#include <vector>
#include <memory>
#include <functional>

namespace nmath {
	namespace util {

		template<typename T, unsigned int L>
		class ArraySimple
		{
		public:
			ArraySimple() :_M_size(0){}
			void push_back(T const & t)
			{
				assert(_M_size < L);
				_M_t[_M_size] = t;
				++_M_size;
			}
			T & operator[](unsigned int i)
			{
				assert(i < _M_size);
				return _M_t[i];
			}
			unsigned int size()
			{
				return _M_size;
			}
		private:
			T _M_t[L];
			unsigned int _M_size;
		};

		template<typename T> class Array;
		/**
		 * reference
		*/
		template<typename T>
		class ArrayRef
		{
		public:
			friend class Array<T>;

			T & ref()
			{
				++std::get<1>(_M_array.lock()->_M_v[_M_i]);
				return std::get<0>(_M_array.lock()->_M_v[_M_i]);
			}
			T const & ref() const
			{
				return std::get<0>(_M_array.lock()->_M_v[_M_i]);
			}

			ArrayRef(std::weak_ptr<Array<T>> arr, unsigned int i) :
				_M_array(arr), 
				_M_i(i)
			{

			}
		private:
			std::weak_ptr<Array<T>> _M_array;
			unsigned int _M_i;
		};
		/**
		* reference
		*/
		template<typename T>
		class ArrayRefIndexRef
		{
		public:
			friend class Array<T>;

			ArrayRefIndexRef(std::weak_ptr<Array<T>> arr, std::function<void(unsigned int)> f_set, std::function<unsigned int()> f_get, unsigned int i) :
				_M_array(arr),
				_M_f_set(f_set),
				_M_f_get(f_get)
			{
				f_set(i);
			}
		private:
			std::function<void(unsigned int)> _M_f_set;
			std::function<unsigned int()> _M_f_get;
			std::weak_ptr<Array<T>> _M_array;
		};
		/**
		 * contianer
		*/
		template<typename T>
		class Array: public std::enable_shared_from_this<Array<T>>
		{
		public:
			friend class ArrayRef<T>;

			typedef std::tuple<T, unsigned int> TUPLE;

			virtual std::shared_ptr< ArrayRef<T> > push_back(T const & t)
			{
				auto r = std::make_shared< ArrayRef<T> >(shared_from_this(), _M_v.size());
				_M_v.push_back(TUPLE(t,0));
				return r;
			}
			std::shared_ptr< ArrayRefIndexRef<T> > push_back_index_ref(
				T const & t, 
				std::function<void(unsigned int)> f_set, 
				std::function<unsigned int()> f_get)
			{
				auto r = std::make_shared< ArrayRefIndexRef<T> >(shared_from_this(), f_set, f_get, _M_v.size());
				_M_v.push_back(TUPLE(t,0));
				return r;
			}
			unsigned int size() const
			{
				return _M_v.size();
			}
		protected:
			std::vector<TUPLE> _M_v;
		};

		/*
		* similar to Array but designed for storing types with dynamic size
		* this implied that T store data elsewhere and a simple byte copy of T would not work
		* therefore T must have a serialize/deserialize function
		*
		* types that will use this class:
		*  * Polytope
		*     * dynamic number of faces
		*  * Face
		*     * dynamic number of boundaries
		*/
		template<typename T>
		class ArrayIndirect : public Array<T> //public std::enable_shared_from_this<ArrayIndirect<T>>
		{
		public:
			friend class ArrayRef<T>;

			ArrayIndirect() : buffer(0), buffer_size(0) {}
			/*
			* for any elements that have changed since last refresh
			* resize if necessary and copy data to buffer
			*/
			void refresh()
			{
				for (int i = 0; i < _M_v.size(); ++i)
				{
					if (std::get<1>(_M_v[i]) > 0)
					{
						char * c = seek(i);

						unsigned int block_size = *((unsigned int*)c);

						unsigned int block_size_new = std::get<0>(_M_v[i]).size_byte() + sizeof(unsigned int);

						if (block_size_new != block_size) resize(i, block_size_new);

						c = seek(i);
						
						*((unsigned int*)c) = block_size_new;
						c += sizeof(unsigned int);
						std::get<0>(_M_v[i]).serialize(c);
					}
				}
			}

			virtual std::shared_ptr< ArrayRef<T> > push_back(T const & t)
			{
				unsigned int index = _M_v.size();
				auto r = std::make_shared< ArrayRef<T> >(shared_from_this(), _M_v.size());
				_M_v.push_back(TUPLE(t,0));

				// write to buffer
				unsigned int l = t.size_byte();
				unsigned int block_size = sizeof(unsigned int) + l;
				resize(buffer_size + block_size);
				char * c = seek(index);
				*((unsigned int *)c) = block_size;
				c += sizeof(unsigned int);
				t.serialize(c);

				return r;
			}
			std::shared_ptr< ArrayRefIndexRef<T> > push_back_index_ref(
				T const & t,
				std::function<void(unsigned int)> f_set,
				std::function<unsigned int()> f_get)
			{
				auto r = std::make_shared< ArrayRefIndexRef<T> >(shared_from_this(), f_set, f_get, _M_v.size());
				_M_v.push_back(t);
				return r;
			}
			unsigned int size() const
			{
				return _M_v.size();
			}

			char * seek(unsigned int i)
			{
				char * c = buffer;

				for (int j = 0; j < i; ++j)
				{
					unsigned int l = *((unsigned int *)c);

					c += l;
				}

				return c;
			}
			char * seek(char * c, unsigned int i)
			{
				for (int j = 0; j < i; ++j)
				{
					unsigned int l = *((unsigned int *)c);

					c += l;
				}

				return c;
			}
			void resize(unsigned int i, unsigned int new_size)
			{
				assert(i < _M_v.size());
				assert(new_size > 0);

				char * c = seek(i);

				unsigned int old_size = *((unsigned int *)c);

				if (new_size == old_size) return;

				// common
				*((unsigned int *)c) = new_size;

				if (new_size < old_size)
				{
					if (i < (buffer_size - 1))
					{
						char * c_old = c + old_size;
						char * c_new = c + new_size;

						memcpy(c_new, c_old, buffer_size - (c_old - buffer));
					}
				}
				else if (new_size > old_size)
				{
					char * new_buffer = new char[buffer_size + new_size - old_size];
					
					memcpy(new_buffer, buffer, c - buffer);

					if (i < (_M_v.size() - 1))
					{
						char * c_old = c + old_size;
						char * c_new = new_buffer + (c - buffer) + new_size;

						memcpy(c_new, c_old, buffer_size - (c_old - buffer));
					}

					delete[] buffer;
					buffer = new_buffer;
				}

				// common
				buffer_size += (new_size - old_size);
			}
			void resize(unsigned int new_size)
			{
				if (new_size <= buffer_size) return;

				char * new_buffer = new char[new_size];

				memcpy(new_buffer, buffer, buffer_size);

				if (buffer) delete[] buffer;
				buffer = new_buffer;

				buffer_size = new_size;
			}

			unsigned int size_buffer()
			{
				return buffer_size;
			}

			void print()
			{
				// for debugging
				char * c = buffer;
				while (true)
				{
					for (int i = 0; i < 4; ++i)
					{
						if (c == (buffer + buffer_size)) break;
						
						//std::cout << std::showbase << std::internal << std::setw(4) << std::hex << *((short*)c) << " ";
						std::cout << *((unsigned int*)c) << " ";
						c += sizeof(int);
					}
					std::cout << std::endl;

					if (c == (buffer + buffer_size)) break;
				}

				std::cout << std::dec;
			}
		private:
			
			/* data storage
			* the buffer is divided into block, one for each element
			* each element starts with an unsigned int that contains the full length of the block in bytes
			*/
			char * buffer;
			unsigned int buffer_size;
		};
	}
}



