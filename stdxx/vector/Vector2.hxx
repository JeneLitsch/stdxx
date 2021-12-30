#pragma once
#include <ostream>
#include "VectorFlavor.hxx"

namespace stx {
	template<class Arithmetic, class Flavor = vectorFlavor::DEFAULT>
	class Vector2 {
	public:
		template<class VectorType>
		static constexpr Vector2 from(const VectorType & vec) {
			return Vector2(
				static_cast<Arithmetic>(vec.x),
				static_cast<Arithmetic>(vec.y));
		}

		constexpr Vector2(const Vector2<Arithmetic, Flavor> & vector)
			:	x(vector.x),
				y(vector.y) {}

		template<class Arithmetic2, class Flavor2>
		explicit constexpr Vector2(const Vector2<Arithmetic2, Flavor2> & vector)
			:	x(static_cast<Arithmetic>(vector.x)),
				y(static_cast<Arithmetic>(vector.y)) {}

		constexpr Vector2() 
			:	x(0), y(0) {}
		
		constexpr Vector2(const Arithmetic x, const Arithmetic y) noexcept
			:	x(x), y(y) {}
		
		constexpr Vector2(const Arithmetic xy)
			:	x(xy), y(xy) {}

		template<class VectorType>
		constexpr VectorType to() const {
			return VectorType(
				static_cast<decltype(VectorType::x)>(this->x),
				static_cast<decltype(VectorType::y)>(this->y));
		}

		virtual constexpr ~Vector2() = default;

		constexpr Vector2 & operator=(const Vector2&) = default;
		constexpr Vector2 & operator=(Vector2 &&) = default;

		Arithmetic x;
		Arithmetic y;
	};

	

	// Typedefs
	using Vector2f = Vector2<float>; 
	using Vector2d = Vector2<double>; 
	using Vector2i = Vector2<int>; 
	using Vector2l = Vector2<long>; 
	using Vector2u = Vector2<unsigned>; 
	using Vector2ul = Vector2<unsigned long>; 

	template<typename Arithmetic> 
	using Size2   = Vector2<Arithmetic, vectorFlavor::SIZE>;
	using Size2f  = Size2<float>;
	using Size2d  = Size2<double>; 
	using Size2i  = Size2<int>;
	using Size2l  = Size2<long>;
	using Size2u  = Size2<unsigned>; 
	using Size2ul = Size2<unsigned long>;


	template<typename Arithmetic> 
	using Position2   = Vector2<Arithmetic, vectorFlavor::POSITION>;
	using Position2f  = Position2<float>; 
	using Position2d  = Position2<double>; 
	using Position2i  = Position2<int>; 
	using Position2l  = Position2<long>; 
	using Position2u  = Position2<unsigned>; 
	using Position2ul = Position2<unsigned long>;
}



// Element-wise binary operators
template<template<class> class Op, class Arithmetic, class FlavorL, class FlavorR>
constexpr auto elementWiseOperator(
	const stx::Vector2<Arithmetic, FlavorL> & l,
	const stx::Vector2<Arithmetic, FlavorR> & r) {

	// Compile time evaluation of return Flavor
	// Return specified flavor if both are the same
	if constexpr (std::same_as<FlavorL, FlavorR>) {
		return stx::Vector2<Arithmetic, FlavorL>(
			Op<Arithmetic>()(l.x, r.x),
			Op<Arithmetic>()(l.y, r.y));
	}
	// Return default flavor if l and r Flavor do not match
	else {
		return stx::Vector2<Arithmetic, stx::vectorFlavor::DEFAULT>(
			Op<Arithmetic>()(l.x, r.x),
			Op<Arithmetic>()(l.y, r.y));
	}
}

template<class Arithmetic, class FlavorL, class FlavorR>
constexpr auto operator+(
	const stx::Vector2<Arithmetic, FlavorL> & l,
	const stx::Vector2<Arithmetic, FlavorR> & r) {
	return elementWiseOperator<std::plus>(l, r); 
}

template<class Arithmetic, class FlavorL, class FlavorR>
constexpr auto operator*(
	const stx::Vector2<Arithmetic, FlavorL> & l,
	const stx::Vector2<Arithmetic, FlavorR> & r) {
	return elementWiseOperator<std::multiplies>(l, r); 
}

template<class Arithmetic, class FlavorL, class FlavorR>
constexpr auto operator-(
	const stx::Vector2<Arithmetic, FlavorL> & l,
	const stx::Vector2<Arithmetic, FlavorR> & r) {
	return elementWiseOperator<std::minus>(l, r); 
}


// Scalar operators
template<template<class> class Op, class Arithmetic, class Flavor>
constexpr auto scalarOperator(
	const stx::Vector2<Arithmetic, Flavor> & vec,
	const Arithmetic & scalar) {
	return stx::Vector2<Arithmetic, Flavor>(
		Op<Arithmetic>()(vec.x, scalar),
		Op<Arithmetic>()(vec.y, scalar));
}

template<class Arithmetic, class Flavor>
constexpr auto operator*(
	const Arithmetic & scalar,
	const stx::Vector2<Arithmetic, Flavor> & vec) {
	return scalarOperator<std::multiplies>(vec, scalar);
}

template<class Arithmetic, class Flavor>
constexpr auto operator*(
	const stx::Vector2<Arithmetic, Flavor> & vec,
	const Arithmetic & scalar) {
	return scalarOperator<std::multiplies>(vec, scalar);
}

template<class Arithmetic, class Flavor>
constexpr auto operator/(
	const stx::Vector2<Arithmetic, Flavor> & vec,
	const Arithmetic & scalar) {
	return scalarOperator<std::divides>(vec, scalar);
}


// Unary
template<class Arithmetic, class Flavor>
constexpr auto operator-(
	const stx::Vector2<Arithmetic, Flavor> & vec) {
	return stx::Vector2<Arithmetic, Flavor>(
		-vec.x,
		-vec.y);
}

template<class Arithmetic, class Flavor>
constexpr auto operator==(
	const stx::Vector2<Arithmetic, Flavor> & l,
	const stx::Vector2<Arithmetic, Flavor> & r) {
	return l.x == r.x && l.y == r.y; 
}

template<class Arithmetic, class Flavor>
constexpr auto operator!=(
	const stx::Vector2<Arithmetic, Flavor> & l,
	const stx::Vector2<Arithmetic, Flavor> & r) {
	return !(l == r); 
}

// Output
template<class Arithmetic, class Flavor>
std::ostream & operator<<(
	std::ostream & stream,
	const stx::Vector2<Arithmetic, Flavor> vector) {
	stream << "(" << vector.x << ", " << vector.y << ")";
	return stream;
}