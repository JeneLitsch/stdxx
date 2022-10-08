#pragma once
#include <type_traits>

namespace stx {
	template<typename T>
	concept signed_numeric = std::is_signed_v<T>;
}