#include <vector>
#include <memory>

namespace nspace {
	namespace util {

		template<typename T> class Array;

		template<typename T>
		class ArrayRef
		{
		public:
			friend class Array<T>;
			ArrayRef(unsigned int i) : _M_i(i)
			{

			}
		private:
			unsigned int _M_i;
		};

		template<typename T>
		class Array
		{
		public:
			std::shared_ptr< ArrayRef<T> > push_back(T const & t)
			{
				auto r = std::make_shared< ArrayRef<T> >(_M_v.size());
				_M_v.push_back(t);
				return r;
			}
		private:
			std::vector<T> _M_v;
		};
	}
}