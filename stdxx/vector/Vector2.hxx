#pragma once
#include <ostream>
#include "VectorN.hxx"


namespace stx {


	template<typename T, typename Flavor = vectorFlavor::DEFAULT>
	using vector2 = vectorN<T, 2, Flavor>;	

	// Typedefs
	using vector2f  = vector2<float>; 
	using vector2d  = vector2<double>; 
	using vector2i  = vector2<int>; 
	using vector2l  = vector2<long>; 
	using vector2u  = vector2<unsigned>; 
	using vector2ul = vector2<unsigned long>; 

	template<typename Arithmetic> 
	using size2   = vector2<Arithmetic, vectorFlavor::SIZE>;
	using size2f  = size2<float>;
	using size2d  = size2<double>; 
	using size2i  = size2<int>;
	using size2l  = size2<long>;
	using size2u  = size2<unsigned>; 
	using size2ul = size2<unsigned long>;


	template<typename Arithmetic> 
	using position2   = vector2<Arithmetic, vectorFlavor::POSITION>;
	using position2f  = position2<float>; 
	using position2d  = position2<double>; 
	using position2i  = position2<int>; 
	using position2l  = position2<long>; 
	using position2u  = position2<unsigned>; 
	using position2ul = position2<unsigned long>;



	// Element-wise binary operators
	template<template<class> class Op, class Arithmetic, class FlavorL, class FlavorR>
	constexpr auto elementWiseOperator(
		const stx::vector2<Arithmetic, FlavorL> & l,
		const stx::vector2<Arithmetic, FlavorR> & r) {

		// Compile time evaluation of return Flavor
		// Return specified flavor if both are the same
		if constexpr (std::same_as<FlavorL, FlavorR>) {
			return stx::vector2<Arithmetic, FlavorL>(
				Op<Arithmetic>()(l.x, r.x),
				Op<Arithmetic>()(l.y, r.y));
		}
		// Return default flavor if l and r Flavor do not match
		else {
			return stx::vector2<Arithmetic, stx::vectorFlavor::DEFAULT>(
				Op<Arithmetic>()(l.x, r.x),
				Op<Arithmetic>()(l.y, r.y));
		}
	}

	template<class Arithmetic, class FlavorL, class FlavorR>
	constexpr auto operator+(
		const stx::vector2<Arithmetic, FlavorL> & l,
		const stx::vector2<Arithmetic, FlavorR> & r) {
		return elementWiseOperator<std::plus>(l, r); 
	}

	template<class Arithmetic, class FlavorL, class FlavorR>
	constexpr auto operator*(
		const stx::vector2<Arithmetic, FlavorL> & l,
		const stx::vector2<Arithmetic, FlavorR> & r) {
		return elementWiseOperator<std::multiplies>(l, r); 
	}

	template<class Arithmetic, class FlavorL, class FlavorR>
	constexpr auto operator/(
		const stx::vector2<Arithmetic, FlavorL> & l,
		const stx::vector2<Arithmetic, FlavorR> & r) {
		return elementWiseOperator<std::divides>(l, r); 
	}

	template<class Arithmetic, class FlavorL, class FlavorR>
	constexpr auto operator-(
		const stx::vector2<Arithmetic, FlavorL> & l,
		const stx::vector2<Arithmetic, FlavorR> & r) {
		return elementWiseOperator<std::minus>(l, r); 
	}


	// Scalar operators
	template<template<class> class Op, class Arithmetic, class Flavor>
	constexpr auto scalarOperator(
		const stx::vector2<Arithmetic, Flavor> & vec,
		const Arithmetic & scalar) {
		return stx::vector2<Arithmetic, Flavor>(
			Op<Arithmetic>()(vec.x, scalar),
			Op<Arithmetic>()(vec.y, scalar));
	}

	template<class Arithmetic, class Flavor>
	constexpr auto operator*(
		const Arithmetic & scalar,
		const stx::vector2<Arithmetic, Flavor> & vec) {
		return scalarOperator<std::multiplies>(vec, scalar);
	}

	template<class Arithmetic, class Flavor>
	constexpr auto operator*(
		const stx::vector2<Arithmetic, Flavor> & vec,
		const Arithmetic & scalar) {
		return scalarOperator<std::multiplies>(vec, scalar);
	}

	template<class Arithmetic, class Flavor>
	constexpr auto operator/(
		const Arithmetic & scalar,
		const stx::vector2<Arithmetic, Flavor> & vec) {
		return scalarOperator<std::divides>(vec, scalar);
	}

	template<class Arithmetic, class Flavor>
	constexpr auto operator/(
		const stx::vector2<Arithmetic, Flavor> & vec,
		const Arithmetic & scalar) {
		return scalarOperator<std::divides>(vec, scalar);
	}


	// Unary
	template<class Arithmetic, class Flavor>
	constexpr auto operator-(
		const stx::vector2<Arithmetic, Flavor> & vec) {
		return stx::vector2<Arithmetic, Flavor>(
			-vec.x,
			-vec.y);
	}

	template<class Arithmetic, class Flavor>
	constexpr auto operator==(
		const stx::vector2<Arithmetic, Flavor> & l,
		const stx::vector2<Arithmetic, Flavor> & r) {
		return l.x == r.x && l.y == r.y; 
	}

	template<class Arithmetic, class Flavor>
	constexpr auto operator!=(
		const stx::vector2<Arithmetic, Flavor> & l,
		const stx::vector2<Arithmetic, Flavor> & r) {
		return !(l == r); 
	}

	// Output
	template<class Arithmetic, class Flavor>
	std::ostream & operator<<(
		std::ostream & stream,
		const stx::vector2<Arithmetic, Flavor> vector) {
		stream << "(" << vector.x << ", " << vector.y << ")";
		return stream;
	}
}
