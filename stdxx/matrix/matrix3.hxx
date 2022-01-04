#pragma once
#include <ostream>
#include <array>
#include "../vector.hxx"
namespace stx {
	template<typename T>
	class matrix3 {
	public:
		constexpr matrix3() {
			this->elements = std::array{
				std::array<T, 3>{1, 0, 0},
				std::array<T, 3>{0, 1, 0},
				std::array<T, 3>{0, 0, 1}};
		}

		constexpr matrix3(
			T a00, T a10, T a20,
			T a01, T a11, T a21,
			T a02, T a12, T a22)
			:	elements({
				std::array<T, 3>{a00, a10, a20}, 
				std::array<T, 3>{a01, a11, a21},
				std::array<T, 3>{a02, a12, a22}}) {}

		constexpr matrix3(
			std::array<T, 3> y0,
			std::array<T, 3> y1,
			std::array<T, 3> y2)
			:	elements({y0, y1, y2})
			{}

		constexpr matrix3(std::array<std::array<T, 3>, 3> elements)
			:	elements(elements) {}

		constexpr inline const T & operator()(std::size_t x, std::size_t y) const {
			return elements[y][x];
		}

		constexpr inline T & operator()(std::size_t x, std::size_t y) {
			return elements[y][x];
		}
	private:
		std::array<std::array<T, 3>, 3> elements;
	};

	template<typename T>
	std::ostream & operator<<(std::ostream & out, const matrix3<T> & m) {
		out << "[";
		for(std::size_t y = 0; y < 3; y++) {
			out << (y ? "|" : "");
			for(std::size_t x = 0; x < 3; x++) {
				out << (x ? "," : "") << m(x,y);
			}
		}
		out << "]";
		return out;
	}

	template<typename T>
	constexpr matrix3<T> operator+(const matrix3<T> & l, const matrix3<T> & r) {
		matrix3<T> m;
		for(std::size_t x = 0; x < 3; x++) {
			for(std::size_t y = 0; y < 3; y++) {
				m(x,y) = l(x,y) + r(x,y);
			}
		}
		return m;
	}

	template<typename T>
	constexpr matrix3<T> operator-(const matrix3<T> & l, const matrix3<T> & r) {
		matrix3<T> m;
		for(std::size_t x = 0; x < 3; x++) {
			for(std::size_t y = 0; y < 3; y++) {
				m(x,y) = l(x,y) - r(x,y);
			}
		}
		return m;
	}

	template<typename T>
	constexpr matrix3<T> operator*(const matrix3<T> & l, const matrix3<T> & r) {
		matrix3<T> m;
		for(std::size_t x = 0; x < 3; x++) {
			for(std::size_t y = 0; y < 3; y++) {
				T value = 0;
				for(std::size_t i = 0; i < 3; i++) {
					value += l(i,y) * r(x,i);
				}
				m(x,y) = value;
			}
		}
		return m;
	}
}