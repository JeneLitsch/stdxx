#pragma once
#include <array>
#include <vector>

template<class T, std::size_t SIZE_L, std::size_t SIZE_R>
std::array<T, SIZE_L + SIZE_R> operator+(
	const std::array<T, SIZE_L> & l,
	const std::array<T, SIZE_R> & r) {
	std::array<sf::Vertex, SIZE_L + SIZE_R> arr;
	std::copy_n(l.begin(), SIZE_L, arr.begin());
	std::copy_n(r.begin(), SIZE_R, arr.begin() + SIZE_L);
	return arr;
}

template<class T, std::size_t SIZE>
std::vector<T> & operator+=(
	std::vector<T> & vec,
	const std::array<T, SIZE> & arr) {
	vec.reserve(vec.size() + SIZE);
	std::copy_n(arr.begin(), SIZE, std::back_inserter(vec));
	return vec;
}