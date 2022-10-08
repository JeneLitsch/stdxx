#pragma once
#include <type_traits>

namespace stx {
	template<typename T>
	concept sized_container = std::is_integral_v<decltype(T{}.size())>;
}