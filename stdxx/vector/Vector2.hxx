#pragma once
#include <ostream>
#include "VectorFlavor.hxx"
#include "../concepts.hxx"
#include "../strong.hxx"

namespace stx {
	template<typename T>
	using radians_t = strong<T, class RADIANS>;

	template<class Arithmetic, class Flavor = vectorFlavor::DEFAULT>
	class vector2 {
	public:
		static constexpr vector2 from(const vector_2 auto & vec) {
			return vector2(
				static_cast<Arithmetic>(vec.x),
				static_cast<Arithmetic>(vec.y));
		}

		static constexpr vector2 from_angle(const radians_t<Arithmetic> angle) {
			return vector2(
				std::cos(stx::collapse(angle)),
				std::sin(stx::collapse(angle)));
		}

		constexpr vector2(const vector2<Arithmetic, Flavor> & vector)
			:	x(vector.x),
				y(vector.y) {}

		template<class Arithmetic2, class Flavor2>
		explicit constexpr vector2(const vector2<Arithmetic2, Flavor2> & vector)
			:	x(static_cast<Arithmetic>(vector.x)),
				y(static_cast<Arithmetic>(vector.y)) {}

		constexpr vector2() 
			:	x(0), y(0) {}
		
		constexpr vector2(const Arithmetic x, const Arithmetic y) noexcept
			:	x(x), y(y) {}
		
		constexpr vector2(const Arithmetic xy)
			:	x(xy), y(xy) {}

		template<class VectorType>
		constexpr VectorType to() const {
			return VectorType(
				static_cast<decltype(VectorType::x)>(this->x),
				static_cast<decltype(VectorType::y)>(this->y));
		}

		virtual constexpr ~vector2() = default;

		constexpr vector2 & operator=(const vector2&) = default;
		constexpr vector2 & operator=(vector2 &&) = default;

		Arithmetic & operator[](std::size_t i) {
			switch (i) {
			case 0: return x;
			case 1: return y;
			default: throw std::out_of_range{"vector2 index out of range"};
			}
		}

		const Arithmetic & operator[](std::size_t i) const {
			switch (i) {
			case 0: return x;
			case 1: return y;
			default: throw std::out_of_range{"vector2 index out of range"};
			}
		}

		Arithmetic x;
		Arithmetic y;
	};

	

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
