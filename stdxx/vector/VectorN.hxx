#pragma once
#include <cstdint>
#include <array>
#include <iostream>
#include <tuple>
#include <functional>
#include "VectorFlavor.hxx"
#include "../concepts.hxx"
#include "../strong.hxx"

namespace stx {
	template<typename T>
	using radians_t = strong<T, class RADIANS>;

	template<typename T, std::size_t N, typename Flavor = vectorFlavor::DEFAULT>
	class vectorN {
	public:
		constexpr vectorN() {
			std::fill(std::begin(this->elements), std::end(this->elements), T{});
		}

		constexpr vectorN(const std::array<T, N> & array)
		: elements {array} {}

		constexpr vectorN(T x) {
			std::fill(std::begin(this->elements), std::end(this->elements), x);
		}

		constexpr vectorN(T x1, auto &&... args)
		: elements{x1, static_cast<T>(args)...} {}

		constexpr T & operator[](std::size_t i) {
			return elements[i];
		}

		constexpr const T & operator[](std::size_t i) const {
			return elements[i];
		}
	private:
		std::array<T, N> elements;
	};

	template<class Arithmetic, class Flavor>
	class vectorN<Arithmetic, 2, Flavor> {
	public:
		static constexpr vectorN from(const stx::vector_2 auto & vec) {
			return vectorN(
				static_cast<Arithmetic>(vec.x),
				static_cast<Arithmetic>(vec.y));
		}

		template<typename X, typename Y>
		static constexpr vectorN from(const std::tuple<X, Y> & tup) {
			auto [x, y] = tup;
			return vectorN{x, y};
		}

		static constexpr vectorN from_angle(const radians_t<Arithmetic> angle) {
			return vectorN(
				std::cos(stx::collapse(angle)),
				std::sin(stx::collapse(angle)));
		}

		constexpr vectorN(const vectorN & vector)
		: x(vector.x), y(vector.y) {}

		constexpr vectorN(const std::array<Arithmetic, 2> & array)
		: x{array[0]}, y{array[1]} {}

		template<class Arithmetic2, class Flavor2>
		explicit constexpr vectorN(const vectorN<Arithmetic2, 2, Flavor2> & vector)
			:	x(static_cast<Arithmetic>(vector.x)),
				y(static_cast<Arithmetic>(vector.y)) {}

		constexpr vectorN() 
			:	x(0), y(0) {}


		
		constexpr vectorN(const Arithmetic x, const Arithmetic y) noexcept
			:	x(x), y(y) {}
		
		constexpr vectorN(const Arithmetic xy)
			:	x(xy), y(xy) {}

		template<class VectorType>
		constexpr VectorType to() const {
			return VectorType(
				static_cast<decltype(VectorType::x)>(this->x),
				static_cast<decltype(VectorType::y)>(this->y));
		}

		virtual constexpr ~vectorN() = default;

		constexpr vectorN & operator=(const vectorN&) = default;
		constexpr vectorN & operator=(vectorN &&) = default;

		constexpr Arithmetic & operator[](std::size_t i) {
			switch (i) {
			case 0: return x;
			case 1: return y;
			default: throw std::out_of_range{"vector2 index out of range"};
			}
		}

		constexpr const Arithmetic & operator[](std::size_t i) const {
			switch (i) {
			case 0: return x;
			case 1: return y;
			default: throw std::out_of_range{"vector2 index out of range"};
			}
		}

		Arithmetic x;
		Arithmetic y;
	};


	template<class Arithmetic, class Flavor>
	class vectorN<Arithmetic, 3, Flavor> {
	public:
		using value_type = Arithmetic;
		constexpr vectorN(Arithmetic x, Arithmetic y, Arithmetic z) noexcept
		: x(x), y(y), z(z) {}

		constexpr vectorN(const std::array<Arithmetic, 3> & array)
		: x{array[0]}, y{array[1]}, z{array[2]} {}

		constexpr vectorN(Arithmetic xyz) noexcept
		: x(xyz), y(xyz), z(xyz) {}

		constexpr vectorN()
		: x(0), y(0), z(0) {}

		template<class Arithmetic2, class Flavor2>
		explicit constexpr vectorN(const vectorN<Arithmetic2, 3, Flavor2> & vector)
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



		constexpr Arithmetic & operator[](std::size_t i) {
			switch (i) {
			case 0: return x;
			case 1: return y;
			case 2: return z;
			default: throw std::out_of_range{"vector2 index out of range"};
			}
		}

		constexpr const Arithmetic & operator[](std::size_t i) const {
			switch (i) {
			case 0: return x;
			case 1: return y;
			case 2: return z;
			default: throw std::out_of_range{"vector2 index out of range"};
			}
		}


		Arithmetic x;
		Arithmetic y;
		Arithmetic z;
	};


	template<typename Op, typename T, std::size_t N, typename FlavorL, typename FlavorR>
	constexpr auto element_wise(
		const vectorN<T, N, FlavorL> & l,
		const vectorN<T, N, FlavorR> & r) {
		
		std::array<T, N> vec;
		for(std::size_t i = 0; i < N; ++i) {
			vec[i] = Op{}(l[i], r[i]);
		}
		if constexpr (std::same_as<FlavorL, FlavorR>) {
			return vectorN<T, N, FlavorL>{vec};
		}
		else {
			return vectorN<T, N, vectorFlavor::DEFAULT>{vec};
		}
	}


	
	template<typename T, std::size_t N, typename FlavorL, typename FlavorR>
	constexpr auto operator+(
		const vectorN<T, N, FlavorL> & l,
		const vectorN<T, N, FlavorR> & r) {

		return element_wise<std::plus<T>>(l, r);
	}



	template<typename T, std::size_t N, typename FlavorL, typename FlavorR>
	constexpr auto operator-(
		const vectorN<T, N, FlavorL> & l,
		const vectorN<T, N, FlavorR> & r) {
			
		return element_wise<std::minus<T>>(l, r);
	}



	template<typename T, std::size_t N, typename FlavorL, typename FlavorR>
	constexpr auto operator*(
		const vectorN<T, N, FlavorL> & l,
		const vectorN<T, N, FlavorR> & r) {
			
		return element_wise<std::multiplies<T>>(l, r);
	}



	template<typename T, std::size_t N, typename FlavorL, typename FlavorR>
	constexpr auto operator/(
		const vectorN<T, N, FlavorL> & l,
		const vectorN<T, N, FlavorR> & r) {
			
		return element_wise<std::divides<T>>(l, r);
	}



	template<typename Op, typename T, std::size_t N, typename Flavor>
	constexpr vectorN<T, N, Flavor> scalar_operation(
		const vectorN<T, N, Flavor> & v,
		const T & scalar) {
		vectorN<T, N, Flavor> vec;
		for(std::size_t i = 0; i < N; ++i) {
			vec[i] = Op{}(v[i], scalar);
		}
		return vec;
	}



	template<typename T, std::size_t N, typename Flavor>
	constexpr vectorN<T, N, Flavor> operator*(
		const vectorN<T, N, Flavor> & v,
		const T & scalar) {
		return scalar_operation<std::multiplies<T>>(v, scalar);
	}



	template<typename T, std::size_t N, typename Flavor>
	constexpr vectorN<T, N, Flavor> operator*(
		const T & scalar,
		const vectorN<T, N, Flavor> & v) {
		return scalar_operation<std::multiplies<T>>(v, scalar);
	}



	template<typename T, std::size_t N, typename Flavor>
	constexpr vectorN<T, N, Flavor> operator/(
		const vectorN<T, N, Flavor> & v,
		const T & scalar) {
		return scalar_operation<std::divides<T>>(v, scalar);
	}



	template<typename T, std::size_t N, typename Flavor>
	constexpr bool operator==(
		const vectorN<T, N, Flavor> & l,
		const vectorN<T, N, Flavor> & r) {
		
		for(std::size_t i = 0; i < N; ++i) {
			if(l[i] != r[i]) return false;
		}
		return true;
	}




	template<typename T, std::size_t N, typename Flavor>
	std::ostream & operator<<(std::ostream & out, const vectorN<T, N, Flavor> & vec) {
		out << "(";
		for(std::size_t i = 0; i < N; ++i) {
			if(i) out << ", ";
			out << vec[i];
		}
		out << ")";
		return out;
	}
}