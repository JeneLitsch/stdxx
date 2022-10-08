#pragma once
#include <concepts>
#include <cmath>
#include "concepts/color.hxx"
#include "concepts/signed_numeric.hxx"
#include "concepts/vector.hxx"
#include "concepts/sized_container.hxx"

namespace stx {
	template<typename Arr>
	concept ranged_array = requires(Arr arr) {
		arr.begin();
		arr.end();
	};



	template<typename T, typename Fx>
	concept binary_fx = requires(Fx fx, T x, T y) {
		std::same_as<decltype(fx(x, y)), T>;
	};



	template<typename T>
	concept string_like = std::is_convertible_v<T, std::string_view>;
}