

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
				return _M_array.lock()->_M_v[_M_i];
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

			std::shared_ptr< ArrayRef<T> > push_back(T const & t)
			{
				auto r = std::make_shared< ArrayRef<T> >(shared_from_this(), _M_v.size());
				_M_v.push_back(t);
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
		private:
			std::vector<T> _M_v;
		};
	}
}

