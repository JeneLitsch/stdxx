#pragma once
#include <array>
#include <vector>
#include <span>

template<typename T, std::size_t SIZE_L, std::size_t SIZE_R>
constexpr inline std::array<T, SIZE_L + SIZE_R> operator+(
	const std::array<T, SIZE_L> & l,
	const std::array<T, SIZE_R> & r) {
	std::array<T, SIZE_L + SIZE_R> arr;
	std::copy_n(l.begin(), SIZE_L, arr.begin());
	std::copy_n(r.begin(), SIZE_R, arr.begin() + SIZE_L);
	return arr;
}



template<typename T, std::size_t SIZE>
constexpr inline std::array<T, SIZE + 1> operator+(
	const std::array<T, SIZE> & l,
	const T & r) {
	std::array<T, SIZE + 1> arr;
	std::copy_n(l.begin(), SIZE, arr.begin());
	arr.back() = r;
	return arr;
}



template<typename T, std::size_t SIZE>
inline std::vector<T> & operator+=(
	std::vector<T> & vec,
	const std::array<T, SIZE> & arr) {	
	for(const auto & e : arr) {
		vec.push_back(e);
	}
	return vec;
}



template<typename T, std::size_t SIZE>
inline std::vector<T> & operator+=(
	std::vector<T> & vec,
	std::array<T, SIZE> && arr) {	
	for(auto & e : arr) {
		vec.push_back(std::move(e));
	}
	return vec;
}



template<typename T>
inline std::vector<T> & operator+=(
	std::vector<T> & vec,
	const std::vector<T> & arr) {	
	for(const auto & e : arr) {
		vec.push_back(e);
	}
	return vec;
}



template<typename T>
inline std::vector<T> & operator+=(
	std::vector<T> & vec,
	std::vector<T> && arr) {	
	for(auto & e : arr) {
		vec.push_back(std::move(e));
	}
	return vec;
}



template<typename T>
inline std::vector<T> & operator+=(
	std::vector<T> & vec,
	const std::span<const T> & arr) {	
	for(const auto & e : arr) {
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



template<class T>
std::vector<T> operator+(
	const std::vector<T> & l,
	const std::vector<T> & r) {

	std::vector<T> vec;
	vec.reserve(l.size() + r.size());
	vec.insert(std::end(vec), l.begin(), l.end());
	vec.insert(std::end(vec), r.begin(), r.end());
	return vec;
}


namespace stx {
	template<typename T>
	inline void append(std::vector<T> & vec, const auto & elems) {
		for(const auto & elem : elems) {
			vec.push_back(elem);
		}
	}


	template<typename Element>
	std::vector<Element> repeat(
		const std::vector<Element> & arr,
		const std::integral auto count) {
		
		std::vector<Element>  output;
		for(std::int64_t i = 0; i < count; ++i) {
			append(output, arr);
		}
		return output;
	}
}