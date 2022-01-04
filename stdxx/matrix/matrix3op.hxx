#pragma once
#include "matrix3.hxx"
namespace stx {
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
}