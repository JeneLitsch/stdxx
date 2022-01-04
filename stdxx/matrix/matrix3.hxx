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

	using matrix3f = matrix3<float>; 
	using matrix3d = matrix3<double>;
}