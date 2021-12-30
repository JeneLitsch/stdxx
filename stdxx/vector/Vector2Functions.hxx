#pragma once
#include "Vector2.hxx"
#include <cmath>

namespace stx {
	template<class Arithmetic, class FlavorL, class FlavorR>
	constexpr Arithmetic dot(
		const Vector2<Arithmetic, FlavorL> & l,
		const Vector2<Arithmetic, FlavorR> & r) {
		return l.x * r.x + l.y * r.y;
	}

	template<class Arithmetic, class FlavorL>
	constexpr Arithmetic hypot(
		const Vector2<Arithmetic, FlavorL> & vector) {
		return std::sqrt(vector.x * vector.x + vector.y * vector.y);
	}

	template<class Arithmetic, class Flavor, class Float>
	constexpr auto lerp(
		const Vector2<Arithmetic, Flavor> & a,
		const Vector2<Arithmetic, Flavor> & b,
		Float t) {
		return Vector2<Arithmetic, Flavor>(
			std::lerp(a.x, b.x, t),
			std::lerp(a.y, b.y, t));
	}

	template<class Arithmetic, class Flavor>
	constexpr auto round(
		const Vector2<Arithmetic, Flavor> & vector) {
		return Vector2<Arithmetic, Flavor> (
			std::round(vector.x),
			std::round(vector.y));
	} 

	template<class Arithmetic, class Flavor>
	constexpr auto floor(
		const Vector2<Arithmetic, Flavor> & vector) {
		return Vector2<Arithmetic, Flavor> (
			std::floor(vector.x),
			std::floor(vector.y));
	} 

	template<class Arithmetic, class Flavor>
	constexpr auto ceil(
		const Vector2<Arithmetic, Flavor> & vector) {
		return Vector2<Arithmetic, Flavor>(
			std::ceil(vector.x),
			std::ceil(vector.y));
	} 

	template<class Arithmetic, class Flavor>
	constexpr auto round(
		const Vector2<Arithmetic, Flavor> & vector, const Arithmetic & fraction) {
		return Vector2<Arithmetic, Flavor> (
			std::round(vector.x / fraction) * fraction,
			std::round(vector.y / fraction) * fraction);
	} 

	template<class Arithmetic, class Flavor>
	constexpr auto distance(
		const Vector2<Arithmetic, Flavor> & l,
		const Vector2<Arithmetic, Flavor> & r) {	
		return hypot(r - l);
	}

	template<class Arithmetic, class Flavor>
	constexpr auto testDelta(
		const Vector2<Arithmetic, Flavor> & l,
		const Vector2<Arithmetic, Flavor> & r,
		Arithmetic epsilon) {
		return std::abs(r.x - l.x) <= epsilon
			&& std::abs(r.y - l.y) <= epsilon;
	}

	template<class Arithmetic>
	constexpr auto center(
		const Size2<Arithmetic> & size) {
		return Position2<Arithmetic>{size / 2.f}; 
	}
}
