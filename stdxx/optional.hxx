#include <optional>

namespace stx {
	template<typename T>
	constexpr std::optional<T> as_optional(const T * ptr) {
		if(ptr) return *ptr;
		return std::nullopt;
	}
}