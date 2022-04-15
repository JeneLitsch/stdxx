#pragma once
#include <array>
#include <vector>
#include <span>

template<typename T, std::size_t SIZE_L, std::size_t SIZE_R>
constexpr inline std::array<T, SIZE_L + SIZE_R> operator+(
	const std::array<T, SIZE_L> & l,
	const std::array<T, SIZE_R> & r) {
	std::array<sf::Vertex, SIZE_L + SIZE_R> arr;
	std::copy_n(l.begin(), SIZE_L, arr.begin());
	std::copy_n(r.begin(), SIZE_R, arr.begin() + SIZE_L);
	return arr;
}

template<typename T, std::size_t SIZE>
inline std::vector<T> & operator+=(
	std::vector<T> & vec,
	const std::array<T, SIZE> & arr) {	
	for(const auto e : arr) {
		vec.push_back(e);
	}
	return vec;
}

template<typename T>
inline std::vector<T> & operator+=(
	std::vector<T> & vec,
	const std::vector<T> & arr) {	
	for(const auto e : arr) {
		vec.push_back(e);
	}
	return vec;
}

template<typename T>
inline std::vector<T> & operator+=(
	std::vector<T> & vec,
	const T & t) {	
	vec.push_back(t);
	return vec;
}

namespace stx {
	template<typename T>
	inline void append(std::vector<T> & vec, const auto & elems) {
		for(const auto & elem : elems) {
			vec.push_back(elem);
		}
	}
}