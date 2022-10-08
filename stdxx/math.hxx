#pragma once
#include "vector.hxx"
#include "math/lerp.hxx"
#include "math/clamp.hxx"
#include "math/mod.hxx"
#include "math/wrapped.hxx"

namespace stx {
	constexpr auto fast_sig(auto x) {
		const auto e = std::numbers::e_v<decltype(x)>;
		return 1 / (1 + std::pow(e, -x)); 
	}

	constexpr auto wrap(auto x, auto y) {
		return mod(mod(x, y) + y, y);
	}
}