#pragma once
#include "matrix.hxx"
namespace stx {
	template<typename T>
	using matrix4 = matrixNxN<T,4>;
	using matrix4f = matrix4<float>; 
	using matrix4d = matrix4<double>;
}