#pragma once
#include <cmath>
#include <algorithm>
#include "../concepts.hxx"

namespace stx {
	template<std::totally_ordered T>
	T clamp(const T & v, const T & lo, const T & hi) {
		return v < lo ? lo : v > hi ? hi : v;
	}



	template<stx::vector_2 Vec>
	Vec clamp(const Vec & v, const Vec  & lo, const Vec  & hi) {
		const auto x = clamp<decltype(v.x)>(v.x, lo.x, hi.x);
		const auto y = clamp<decltype(v.y)>(v.y, lo.y, hi.y);
		return Vec{x, y};
	}


	template<stx::vector_3 Vec>
	Vec clamp(const Vec & v, const Vec  & lo, const Vec  & hi) {
		const auto x = clamp<decltype(v.x)>(v.x, lo.x, hi.x);
		const auto y = clamp<decltype(v.y)>(v.y, lo.y, hi.y);
		const auto z = clamp<decltype(v.z)>(v.z, lo.z, hi.z);
		return Vec{x, y, z};
	}
}