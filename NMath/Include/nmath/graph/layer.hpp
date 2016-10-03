

#include <memory>

#include <nmath/graph/decl.hpp>

namespace nmath {
	namespace graph {

		class layer : public std::enable_shared_from_this<::nmath::graph::layer>
		{
		public:
			layer();

			bool	enabled() const;

			bool	_M_enabled;
		};
	}
}
