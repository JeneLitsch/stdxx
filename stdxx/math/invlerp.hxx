#pragma once
#include <concepts>

namespace stx {
	template<typename F>
	requires std::floating_point<F>
	double invlerp(F a, F b, F x) {
		return (x - a) / (b - a);
	}



	template<typename I>
	requires std::signed_integral<I>
	double invlerp(I a, I b, I x) {
		return static_cast<double>(x - a) / static_cast<double>(b - a);
	}



	template<typename U>
	requires std::unsigned_integral<U>
	auto invlerp(U a, U b, U x) {
		const auto l = std::min(a, b);
		const auto h = std::max(a, b);
		const auto t 
			= (static_cast<double>(x) - static_cast<double>(l))
			/ (static_cast<double>(h) - static_cast<double>(l));

		return a < b ? t : 1 - t;
	}
}