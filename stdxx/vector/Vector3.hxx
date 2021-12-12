#pragma once
#include "VectorFlavor.hxx"

namespace stx {
	template<class Arithmetic, class Flavor>
	class Vector3 {
	public:
		constexpr Vector3(Arithmetic x, Arithmetic y, Arithmetic z) noexcept
			:	x(x), y(y), z(z) {}

		constexpr Vector3(Arithmetic xyz) noexcept
			:	x(xyz), y(xyz), z(xyz) {}

		constexpr Vector3()
			:	x(0), y(0), z(0) {}

		template<class VectorType>
		constexpr VectorType to() const {
			return VectorType{
				static_cast<decltype(VectorType::x)>(this->x),
				static_cast<decltype(VectorType::y)>(this->y),
				static_cast<decltype(VectorType::z)>(this->z)};
		}

		Arithmetic x;
		Arithmetic y;
		Arithmetic z;
	};

	using Vector3f = Vector3<float, 			vectorFlavor::DEFAULT>; 
	using Vector3d = Vector3<double,			vectorFlavor::DEFAULT>; 
	using Vector3i = Vector3<int, 				vectorFlavor::DEFAULT>; 
	using Vector3l = Vector3<long, 				vectorFlavor::DEFAULT>; 
	using Vector3u = Vector3<unsigned, 			vectorFlavor::DEFAULT>; 
	using Vector3ul = Vector3<unsigned long, 	vectorFlavor::DEFAULT>; 

	using Size3f = Vector3<float, 				vectorFlavor::SIZE>; 
	using Size3d = Vector3<double,				vectorFlavor::SIZE>; 
	using Size3i = Vector3<int, 				vectorFlavor::SIZE>; 
	using Size3l = Vector3<long, 				vectorFlavor::SIZE>; 
	using Size3u = Vector3<unsigned, 			vectorFlavor::SIZE>; 
	using Size3ul = Vector3<unsigned long, 		vectorFlavor::SIZE>; 

	using Position3f = Vector3<float, 			vectorFlavor::POSITION>;
	using Position3d = Vector3<double,			vectorFlavor::POSITION>;
	using Position3i = Vector3<int, 			vectorFlavor::POSITION>;
	using Position3l = Vector3<long, 			vectorFlavor::POSITION>;
	using Position3u = Vector3<unsigned, 		vectorFlavor::POSITION>;
	using Position3ul = Vector3<unsigned long, 	vectorFlavor::POSITION>;
}



// Elementwise Binary operator
template<template<class> class Op, class Arithmetic , class FlavorL, class FlavorR>
constexpr auto elementWiseOperator(
	const stx::Vector3<Arithmetic, FlavorL> & l,
	const stx::Vector3<Arithmetic, FlavorR> & r) {
	if constexpr (std::same_as<FlavorL, FlavorR>) {
		return stx::Vector3<Arithmetic, FlavorL>(
			Op<Arithmetic>()(l.x, r.x),
			Op<Arithmetic>()(l.y, r.y),
			Op<Arithmetic>()(l.z, r.z));
	}
	else {
		return Vector3<Arithmetic, stx::vectorFlavor::DEFAULT>(
			Op<Arithmetic>()(l.x, r.x),
			Op<Arithmetic>()(l.y, r.y),
			Op<Arithmetic>()(l.z, r.z));
	}

}

template<class Arithmetic, class FlavorL, class FlavorR>
constexpr auto operator+(
	const stx::Vector3<Arithmetic, FlavorL> & l,
	const stx::Vector3<Arithmetic, FlavorL> & r) {
	return elementWiseOperator<std::plus>(l, r);
}

template<class Arithmetic, class FlavorL, class FlavorR>
constexpr auto operator-(
	const stx::Vector3<Arithmetic, FlavorL> & l,
	const stx::Vector3<Arithmetic, FlavorL> & r) {
	return elementWiseOperator<std::minus>(l, r);
}

template<class Arithmetic, class FlavorL, class FlavorR>
constexpr auto operator*(
	const stx::Vector3<Arithmetic, FlavorL> & l,
	const stx::Vector3<Arithmetic, FlavorL> & r) {
	return elementWiseOperator<std::multiplies>(l, r);
}


// Scalar operators
template<template<class> class Op, class Arithmetic, class Flavor> 
constexpr auto scalarOperator(
	const stx::Vector3<Arithmetic, Flavor> & vector,
	const Arithmetic & scalar) {
	return stx::Vector3<Arithmetic, Flavor>(
		Op<Arithmetic>()(vector.x, scalar),
		Op<Arithmetic>()(vector.y, scalar),
		Op<Arithmetic>()(vector.z, scalar));
}

template<class Arithmetic, class Flavor> 
constexpr auto operator *(
	const Arithmetic & scalar,
	const stx::Vector3<Arithmetic, Flavor> & vector) {
	return scalarOperator<std::multiplies>(vector, scalar);
}

template<class Arithmetic, class Flavor> 
constexpr auto operator *(
	const stx::Vector3<Arithmetic, Flavor> & vector,
	const Arithmetic & scalar) {
	return scalarOperator<std::multiplies>(vector, scalar);
}

template<class Arithmetic, class Flavor> 
constexpr auto operator/(
	const stx::Vector3<Arithmetic, Flavor> & vector,
	const Arithmetic & scalar) {
	return scalarOperator<std::divides>(vector, scalar);
}


// Unary
template<class Arithmetic, class Flavor> 
constexpr auto operator-(
	const stx::Vector3<Arithmetic, Flavor> & vector) {
	return stx::Vector3<Arithmetic, Flavor>(
		-vector.x,
		-vector.y,
		-vector.z);
}