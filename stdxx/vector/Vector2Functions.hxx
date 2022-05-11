#pragma once
#include "Vector2.hxx"
#include <cmath>

namespace stx {

	
	template<class Arithmetic, class FlavorL, class FlavorR>
	constexpr Arithmetic dot(
		const vector2<Arithmetic, FlavorL> & l,
		const vector2<Arithmetic, FlavorR> & r) {
		return l.x * r.x + l.y * r.y;
	}

	template<class Arithmetic, class FlavorL>
	constexpr Arithmetic hypot(
		const vector2<Arithmetic, FlavorL> & vector) {
		return std::sqrt(vector.x * vector.x + vector.y * vector.y);
	}


	template<class Arithmetic, class Flavor>
	constexpr auto round(
		const vector2<Arithmetic, Flavor> & vector) {
		return vector2<Arithmetic, Flavor> (
			std::round(vector.x),
			std::round(vector.y));
	} 

	template<class Arithmetic, class Flavor>
	constexpr auto floor(
		const vector2<Arithmetic, Flavor> & vector) {
		return vector2<Arithmetic, Flavor> (
			std::floor(vector.x),
			std::floor(vector.y));
	} 

	template<class Arithmetic, class Flavor>
	constexpr auto ceil(
		const vector2<Arithmetic, Flavor> & vector) {
		return vector2<Arithmetic, Flavor>(
			std::ceil(vector.x),
			std::ceil(vector.y));
	} 

	template<class Arithmetic, class Flavor>
	constexpr auto round(
		const vector2<Arithmetic, Flavor> & vector, const Arithmetic & fraction) {
		return vector2<Arithmetic, Flavor> (
			std::round(vector.x / fraction) * fraction,
			std::round(vector.y / fraction) * fraction);
	} 

	template<class Arithmetic, class Flavor>
	constexpr auto distance(
		const vector2<Arithmetic, Flavor> & l,
		const vector2<Arithmetic, Flavor> & r) {	
		return hypot(r - l);
	}

	template<class Arithmetic, class Flavor>
	constexpr auto testDelta(
		const vector2<Arithmetic, Flavor> & l,
		const vector2<Arithmetic, Flavor> & r,
		Arithmetic epsilon) {
		return std::abs(r.x - l.x) <= epsilon
			&& std::abs(r.y - l.y) <= epsilon;
	}

	template<class Arithmetic>
	constexpr auto center(
		const size2<Arithmetic> & size) {
		return position2<Arithmetic>{size / 2.f}; 
	}

	template<class Arithmetic, class Flavor>
	constexpr radians_t<Arithmetic> angle(const vector2<Arithmetic, Flavor> & v) {
		return std::atan2(v.y, v.x);
	}

	template<class Arithmetic, class Flavor>
	constexpr auto rotate_90_cw(const vector2<Arithmetic, Flavor> & v) {
		return vector2<Arithmetic, Flavor>(-v.y, v.x);
	}

	template<class Arithmetic, class Flavor>
	constexpr auto rotate_90_ccw(const vector2<Arithmetic, Flavor> & v) {
		return vector2<Arithmetic, Flavor>(v.y, -v.x);
	}
}
