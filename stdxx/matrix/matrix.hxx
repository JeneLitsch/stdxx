#pragma once
#include <ostream>
#include <array>
#include "../vector.hxx"
namespace stx {
	template<typename T, std::size_t N, std::size_t M>
	class matrix {
	public:
		constexpr inline const T & operator()(std::size_t x, std::size_t y) const {
			return elements[y][x];
		}

		constexpr inline T & operator()(std::size_t x, std::size_t y) {
			return elements[y][x];
		}
	private:
		std::array<std::array<T, M>, N> elements;
	};

	template<typename T>
	class matrix<T, 3, 3> {
	public:
		constexpr matrix() {
			this->elements = std::array{
				std::array<T, 3>{1, 0, 0},
				std::array<T, 3>{0, 1, 0},
				std::array<T, 3>{0, 0, 1}};
		}

		constexpr matrix(
			T a00, T a10, T a20,
			T a01, T a11, T a21,
			T a02, T a12, T a22)
			:	elements({
				std::array<T, 3>{a00, a10, a20}, 
				std::array<T, 3>{a01, a11, a21},
				std::array<T, 3>{a02, a12, a22}}) {}

		constexpr matrix(
			std::array<T, 3> y0,
			std::array<T, 3> y1,
			std::array<T, 3> y2)
			:	elements({y0, y1, y2})
			{}

		constexpr matrix(std::array<std::array<T, 3>, 3> elements)
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
	class matrix<T, 4, 4> {
	public:
		constexpr matrix() {
			this->elements = std::array{
				std::array<T, 4>{1, 0, 0, 0},
				std::array<T, 4>{0, 1, 0, 0},
				std::array<T, 4>{0, 0, 1, 0},
				std::array<T, 4>{0, 0, 0, 1},
			};
		}

		constexpr matrix(std::array<std::array<T, 4>, 4> elements) : elements {elements} {}
		
		constexpr inline const T & operator()(std::size_t x, std::size_t y) const {
			return elements[y][x];
		}

		constexpr inline T & operator()(std::size_t x, std::size_t y) {
			return elements[y][x];
		}

		template<typename Quat>
		constexpr static matrix from_quat(const Quat & q) {
			const matrix m1 { std::array {
				std::array {  q.w,  q.z, -q.y, q.x },
				std::array { -q.z,  q.w,  q.x, q.y },
				std::array {  q.y, -q.x,  q.w, q.z },
				std::array { -q.x, -q.y, -q.z, q.w },
			}};
			const matrix m2 { std::array {
				std::array {  q.w,  q.z, -q.y, -q.x },
				std::array { -q.z,  q.w,  q.x, -q.y },
				std::array {  q.y, -q.x,  q.w, -q.z },
				std::array {  q.x,  q.y,  q.z,  q.w },
			}};
			return m1 * m2;
		}
	private:
		std::array<std::array<T, 4>, 4> elements;
	};

	template<typename T, std::size_t N>
	using matrixNxN = matrix<T, N, N>;
}