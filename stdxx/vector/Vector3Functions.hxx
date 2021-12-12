#pragma once
#include "Vector2.hxx"
#include "Vector3.hxx"

namespace stx {
	template<class Arithmetic, class FlavorL, class FlavorR>
	Arithmetic dot(
		const Vector3<Arithmetic, FlavorL> & l,
		const Vector3<Arithmetic, FlavorR> & r) {
		return (l.x * r.x) + (l.y * r.y) + (l.z * r.z);
	}

	template<class Arithmetic, class Flavor>
	constexpr auto sliceXY(
		const Vector3<Arithmetic, Flavor> & vector) {
		return Vector2<Arithmetic, Flavor>(vector.x, vector.y);
	}

	template<class Arithmetic, class Flavor>
	constexpr auto extend(
		const Vector2<Arithmetic, Flavor> & vector,
		const Arithmetic & z) {
		return Vector3<Arithmetic, Flavor>(vector.x, vector.y, z);
	}
}

