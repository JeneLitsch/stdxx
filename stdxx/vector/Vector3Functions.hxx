#pragma once
#include "Vector2.hxx"
#include "Vector3.hxx"

namespace stx {
	template<class Arithmetic, class FlavorL, class FlavorR>
	Arithmetic dot(
		const vector3<Arithmetic, FlavorL> & l,
		const vector3<Arithmetic, FlavorR> & r) {
		return (l.x * r.x) + (l.y * r.y) + (l.z * r.z);
	}

	template<class Arithmetic, class Flavor>
	constexpr auto sliceXY(
		const vector3<Arithmetic, Flavor> & vector) {
		return vector2<Arithmetic, Flavor>(vector.x, vector.y);
	}

	template<class Arithmetic, class Flavor>
	constexpr auto extend(
		const vector2<Arithmetic, Flavor> & vector,
		const Arithmetic & z) {
		return vector3<Arithmetic, Flavor>(vector.x, vector.y, z);
	}


	template<class Arithmetic, class Flavor>
	constexpr auto round(
		const vector3<Arithmetic, Flavor> & vector) {
		return vector3<Arithmetic, Flavor> (
			std::round(vector.x),
			std::round(vector.y),
			std::round(vector.z)
		);
	} 

	template<class Arithmetic, class Flavor>
	constexpr auto floor(
		const vector3<Arithmetic, Flavor> & vector) {
		return vector3<Arithmetic, Flavor> (
			std::floor(vector.x),
			std::floor(vector.y),
			std::floor(vector.z)
		);
	} 

	template<class Arithmetic, class Flavor>
	constexpr auto ceil(
		const vector3<Arithmetic, Flavor> & vector) {
		return vector3<Arithmetic, Flavor>(
			std::ceil(vector.x),
			std::ceil(vector.y),
			std::ceil(vector.z)
		);
	} 

	
	template<class Arithmetic, class FlavorL>
	constexpr Arithmetic hypot(
		const vector3<Arithmetic, FlavorL> & vector) {
		return std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
	}


	template<std::floating_point Arithmetic, class FlavorL>
	constexpr vector3<Arithmetic, FlavorL> normalized(
		const vector3<Arithmetic, FlavorL> & vector) {
		return vector / stx::hypot(vector);
	}
}

