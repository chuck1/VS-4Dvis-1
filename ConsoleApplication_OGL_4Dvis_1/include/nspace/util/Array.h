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
		private:
			int _M_i;
		};

		template<typename T>
		class Array
		{
		public:
			std::shared_ptr< ArrayRef<T> >	push(T const & t)
			{
				_M_v.push_back(t);
				auto r = std::make_shared< ArrayRef<T> >
			}

			std::vector<T> _M_v;
		};
	}
}