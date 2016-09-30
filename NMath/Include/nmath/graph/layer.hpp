

#include <memory>

namespace nmath {
	namespace graph {

		class layer : public std::enable_shared_from_this<layer>
		{
		public:
			layer();

			bool	enabled() const;

			bool	_M_enabled;
		};
	}
}