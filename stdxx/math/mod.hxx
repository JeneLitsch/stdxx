#pragma once
#include <numbers>
#include <cmath>

namespace stx {
	constexpr auto mod(std::floating_point auto x, std::floating_point auto y) {
		return std::fmod(x, y);
	}

	constexpr auto mod(std::integral auto x, std::integral auto y) {
		return x % y;
	}
}