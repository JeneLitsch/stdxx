#pragma once
#include "VectorFlavor.hxx"

namespace stx {
	template<class Arithmetic, class Flavor>
	class vector3 {
	public:
		using value_type = Arithmetic;
		constexpr vector3(Arithmetic x, Arithmetic y, Arithmetic z) noexcept
			:	x(x), y(y), z(z) {}

		constexpr vector3(Arithmetic xyz) noexcept
			:	x(xyz), y(xyz), z(xyz) {}

		constexpr vector3()
			:	x(0), y(0), z(0) {}

		template<class Arithmetic2, class Flavor2>
		explicit constexpr vector3(const vector3<Arithmetic2, Flavor2> & vector)
			:	x(static_cast<Arithmetic>(vector.x)),
				y(static_cast<Arithmetic>(vector.y)),
				z(static_cast<Arithmetic>(vector.z)) {}

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