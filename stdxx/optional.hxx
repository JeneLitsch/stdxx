#include <optional>

namespace stx {
	template<typename T>
	constexpr std::optional<T> opt_from_ptr(const T * ptr) {
		if(ptr) return *ptr;
		return std::nullopt;
	}
}