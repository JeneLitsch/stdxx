#pragma once
#include "matrix.hxx"
namespace stx {
	template<typename T>
	using matrix3 = matrixNxN<T,3>;
	using matrix3f = matrix3<float>; 
	using matrix3d = matrix3<double>;
}