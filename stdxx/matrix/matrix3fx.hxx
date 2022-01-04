#pragma once
#include "matrix3.hxx"

namespace stx {
	template<typename T>
	constexpr inline T det(const matrix3<T> & m) {
		return m(0, 0) * (m(1, 1) * m(2, 2) - m(2, 1) * m(1, 2)) 
		     - m(0, 1) * (m(1, 0) * m(2, 2) - m(1, 2) * m(2, 0)) 
	         + m(0, 2) * (m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0));
	}

	template<typename T>
	constexpr inline matrix3<T> inverse(const matrix3<T> & m) {
		const auto det = stx::det(m);
		const auto invdet = 1 / det;
		return stx::matrix3<T> {
			(m(1, 1) * m(2, 2) - m(2, 1) * m(1, 2)) * invdet,
			(m(0, 2) * m(2, 1) - m(0, 1) * m(2, 2)) * invdet,
			(m(0, 1) * m(1, 2) - m(0, 2) * m(1, 1)) * invdet,
			(m(1, 2) * m(2, 0) - m(1, 0) * m(2, 2)) * invdet,
			(m(0, 0) * m(2, 2) - m(0, 2) * m(2, 0)) * invdet,
			(m(1, 0) * m(0, 2) - m(0, 0) * m(1, 2)) * invdet,
			(m(1, 0) * m(2, 1) - m(2, 0) * m(1, 1)) * invdet,
			(m(2, 0) * m(0, 1) - m(0, 0) * m(2, 1)) * invdet,
			(m(0, 0) * m(1, 1) - m(1, 0) * m(0, 1)) * invdet};
	}
}