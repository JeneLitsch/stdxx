#pragma once
#include <cmath>
#include <algorithm>
#include "../concepts.hxx"

namespace stx {

	template<typename T>
	concept default_clampable = requires(T v, T lo, T hi) {
		v < lo ? lo : v > hi ? hi : v;
	};



	auto clamp(
		const default_clampable auto & v,
		const default_clampable auto & lo,
		const default_clampable auto & hi) {
		return v < lo ? lo : v > hi ? hi : v;
	}



	auto clamp(
		const vector_2 auto & v,
		const vector_2 auto & lo,
		const vector_2 auto & hi) {
		using U = decltype(v.x);
		const auto x = clamp<U>(v.x, lo.x, hi.x);
		const auto y = clamp<U>(v.y, lo.y, hi.y);
		return decltype(v) {x, y};
	}
}