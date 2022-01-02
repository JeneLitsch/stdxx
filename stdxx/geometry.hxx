#pragma once
#include "vector.hxx"

namespace stx {
	template<typename Arithmetic>
	constexpr auto align_center(
		const stx::size2<Arithmetic> outer,
		const stx::size2<Arithmetic> inner) {
		return stx::center(outer) - stx::center(inner); 
	}

	template<typename Arithmetic>
	constexpr auto align_bottom(
		const stx::size2<Arithmetic> outer,
		const stx::size2<Arithmetic> inner,
		const Arithmetic gap = 0) {
		const auto x = outer.x / 2 - inner.x / 2;
		const auto y = outer.y - inner.y - gap;
		return stx::position2<Arithmetic>(x,y);
	}
}
