#pragma once
#include <numbers>
#include <cmath>
#include "vector.hxx"

namespace stx {
	constexpr auto fast_sig(auto x) {
		const auto e = std::numbers::e_v<decltype(x)>;
		return 1 / (1 + std::pow(e, -x)); 
	}
}