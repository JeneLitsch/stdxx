#pragma once
#include <numbers>
#include <cmath>
#include "vector.hxx"

namespace stx {
	constexpr auto fast_sig(auto x) {
		const auto e = std::numbers::e_v<decltype(x)>;
		return 1 / (1 + std::pow(e, -x)); 
	}

	constexpr auto mod(std::floating_point auto x, std::floating_point auto y) {
		return std::fmod(x, y);
	}

	constexpr auto mod(std::integral auto x, std::integral auto y) {
		return x % y;
	}

	constexpr auto wrap(auto x, auto y) {
		return  mod(mod(x, y) + y, y);
	}
}