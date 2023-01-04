#pragma once
#include "clamp.hxx"

namespace stx::ease {
	inline constexpr double none(double t) {
		return t;
	}


	inline constexpr double clamp(double t) {
		return stx::clamp(t, 0.0, 1.0);
	}



	inline constexpr auto clamped(auto ease) {
		return [ease] (double t) {
			return clamp(ease(t));
		};
	}



	inline constexpr auto poly_in(double degree) {
		return [degree] (double t) {
			return std::pow(t, degree);
		};
	}



	inline constexpr auto poly_out(double degree) {
		return [degree] (double t) {
			return std::pow(1-(1 - t), degree);
		};
	}



	inline constexpr auto poly_in_out(double degree_in, double degree_out) {
		return [degree_in, degree_out] (double t) {
			return (poly_in(degree_in)(t) + poly_out(degree_out)(t)) / 2.0;
		};
	}



	inline constexpr auto poly_in_out(double degree) {
		return poly_in_out(degree, degree);
	}
}