#pragma once
#include "VectorN.hxx"

namespace stx {
	template<typename T, typename Flavor>
	using vector3 = vectorN<T, 3, Flavor>;

	using vector3f = vector3<float, 			vectorFlavor::DEFAULT>; 
	using vector3d = vector3<double,			vectorFlavor::DEFAULT>; 
	using vector3i = vector3<int, 				vectorFlavor::DEFAULT>; 
	using vector3l = vector3<long, 				vectorFlavor::DEFAULT>; 
	using vector3u = vector3<unsigned, 			vectorFlavor::DEFAULT>; 
	using vector3ul = vector3<unsigned long, 	vectorFlavor::DEFAULT>; 

	using size3f = vector3<float, 				vectorFlavor::SIZE>; 
	using size3d = vector3<double,				vectorFlavor::SIZE>; 
	using size3i = vector3<int, 				vectorFlavor::SIZE>; 
	using size3l = vector3<long, 				vectorFlavor::SIZE>; 
	using size3u = vector3<unsigned, 			vectorFlavor::SIZE>; 
	using size3ul = vector3<unsigned long, 		vectorFlavor::SIZE>; 

	using position3f = vector3<float, 			vectorFlavor::POSITION>;
	using position3d = vector3<double,			vectorFlavor::POSITION>;
	using position3i = vector3<int, 			vectorFlavor::POSITION>;
	using position3l = vector3<long, 			vectorFlavor::POSITION>;
	using position3u = vector3<unsigned, 		vectorFlavor::POSITION>;
	using position3ul = vector3<unsigned long, 	vectorFlavor::POSITION>;
}



// Elementwise Binary operator
template<template<class> class Op, class Arithmetic , class FlavorL, class FlavorR>
constexpr auto elementWiseOperator(
	const stx::vector3<Arithmetic, FlavorL> & l,
	const stx::vector3<Arithmetic, FlavorR> & r) {
	if constexpr (std::same_as<FlavorL, FlavorR>) {
		return stx::vector3<Arithmetic, FlavorL>(
			Op<Arithmetic>()(l.x, r.x),
			Op<Arithmetic>()(l.y, r.y),
			Op<Arithmetic>()(l.z, r.z));
	}
	else {
		return stx::vector3<Arithmetic, stx::vectorFlavor::DEFAULT>(
			Op<Arithmetic>()(l.x, r.x),
			Op<Arithmetic>()(l.y, r.y),
			Op<Arithmetic>()(l.z, r.z));
	}

}

template<class Arithmetic, class FlavorL, class FlavorR>
constexpr auto operator+(
	const stx::vector3<Arithmetic, FlavorL> & l,
	const stx::vector3<Arithmetic, FlavorR> & r) {
	return elementWiseOperator<std::plus>(l, r);
}

template<class Arithmetic, class FlavorL, class FlavorR>
constexpr auto operator-(
	const stx::vector3<Arithmetic, FlavorL> & l,
	const stx::vector3<Arithmetic, FlavorR> & r) {
	return elementWiseOperator<std::minus>(l, r);
}

template<class Arithmetic, class FlavorL, class FlavorR>
constexpr auto operator*(
	const stx::vector3<Arithmetic, FlavorL> & l,
	const stx::vector3<Arithmetic, FlavorR> & r) {
	return elementWiseOperator<std::multiplies>(l, r);
}

template<class Arithmetic, class FlavorL, class FlavorR>
constexpr auto operator/(
	const stx::vector3<Arithmetic, FlavorL> & l,
	const stx::vector3<Arithmetic, FlavorR> & r) {
	return elementWiseOperator<std::divides>(l, r);
}


// Scalar operators
template<template<class> class Op, class Arithmetic, class Flavor> 
constexpr auto scalarOperator(
	const stx::vector3<Arithmetic, Flavor> & vector,
	const Arithmetic & scalar) {
	return stx::vector3<Arithmetic, Flavor>(
		Op<Arithmetic>()(vector.x, scalar),
		Op<Arithmetic>()(vector.y, scalar),
		Op<Arithmetic>()(vector.z, scalar));
}

template<class Arithmetic, class Flavor> 
constexpr auto operator *(
	const Arithmetic & scalar,
	const stx::vector3<Arithmetic, Flavor> & vector) {
	return scalarOperator<std::multiplies>(vector, scalar);
}

template<class Arithmetic, class Flavor> 
constexpr auto operator *(
	const stx::vector3<Arithmetic, Flavor> & vector,
	const Arithmetic & scalar) {
	return scalarOperator<std::multiplies>(vector, scalar);
}

template<class Arithmetic, class Flavor> 
constexpr auto operator/(
	const stx::vector3<Arithmetic, Flavor> & vector,
	const Arithmetic & scalar) {
	return scalarOperator<std::divides>(vector, scalar);
}


// Unary
template<class Arithmetic, class Flavor> 
constexpr auto operator-(
	const stx::vector3<Arithmetic, Flavor> & vector) {
	return stx::vector3<Arithmetic, Flavor>(
		-vector.x,
		-vector.y,
		-vector.z);
}


// Output
template<class Arithmetic, class Flavor>
std::ostream & operator<<(
	std::ostream & stream,
	const stx::vector3<Arithmetic, Flavor> vector) {
	stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
	return stream;
}



template<class Arithmetic, class Flavor>
constexpr auto operator==(
	const stx::vector3<Arithmetic, Flavor> & l,
	const stx::vector3<Arithmetic, Flavor> & r) {
	return l.x == r.x && l.y == r.y && l.z == r.z; 
}



template<class Arithmetic, class Flavor>
constexpr auto operator!=(
	const stx::vector3<Arithmetic, Flavor> & l,
	const stx::vector3<Arithmetic, Flavor> & r) {
	return !(l == r); 
}