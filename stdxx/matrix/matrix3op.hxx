#pragma once
#include "matrix.hxx"
#include "matrix3.hxx"
namespace stx {
	template<typename T, std::size_t N>
	std::ostream & operator<<(std::ostream & out, const matrixNxN<T, N> & m) {
		out << "[";
		for(std::size_t y = 0; y < N; y++) {
			out << (y ? "|" : "");
			for(std::size_t x = 0; x < N; x++) {
				out << (x ? "," : "") << m(x,y);
			}
		}
		out << "]";
		return out;
	}

	template<typename T, std::size_t N>
	constexpr matrixNxN<T, N> operator+(const matrixNxN<T, N> & l, const matrixNxN<T, N> & r) {
		matrixNxN<T, N> m;
		for(std::size_t x = 0; x < N; x++) {
			for(std::size_t y = 0; y < N; y++) {
				m(x,y) = l(x,y) + r(x,y);
			}
		}
		return m;
	}

	template<typename T, std::size_t N>
	constexpr matrixNxN<T, N> operator-(const matrixNxN<T, N> & l, const matrixNxN<T, N> & r) {
		matrixNxN<T, N> m;
		for(std::size_t x = 0; x < N; x++) {
			for(std::size_t y = 0; y < N; y++) {
				m(x,y) = l(x,y) - r(x,y);
			}
		}
		return m;
	}

	template<typename T, std::size_t N>
	constexpr matrixNxN<T, N> operator*(const matrixNxN<T, N> & l, const matrixNxN<T, N> & r) {
		matrixNxN<T, N> m;
		for(std::size_t x = 0; x < N; x++) {
			for(std::size_t y = 0; y < N; y++) {
				T value = 0;
				for(std::size_t i = 0; i < N; i++) {
					value += l(i,y) * r(x,i);
				}
				m(x,y) = value;
			}
		}
		return m;
	}

	template<typename T, class Flavor>
	constexpr vector3<T, Flavor> operator*(
		const matrix3<T> & l,
		const vector3<T, Flavor> & r) {
		vector3<T, Flavor> v;
		
		v.x += r.x * l(0, 0);
		v.x += r.y * l(1, 0);
		v.x += r.z * l(2, 0);
		
		v.y += r.x * l(0, 1);
		v.y += r.y * l(1, 1);
		v.y += r.z * l(2, 1);
		
		v.z += r.x * l(0, 2);
		v.z += r.y * l(1, 2);
		v.z += r.z * l(2, 2);

		return v;
	}

	template<typename T, std::size_t N, class Flavor>
	constexpr vectorN<T, N, Flavor> operator*(
		const matrix<T, N, N> & l,
		const vectorN<T, N, Flavor> & r) {
		vectorN<T, N, Flavor> v;

		for(std::size_t i = 0; i < N; i++) {
			for(std::size_t ii = 0; ii < N; ii++) {
				v[i] += r[ii] * l(ii, i);
			}
		}

		return v;
	}
}