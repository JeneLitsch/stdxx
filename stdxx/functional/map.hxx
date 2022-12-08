#pragma once
#include <vector>

namespace stx::fx {
	template<typename T, typename ... Args>
	constexpr auto map(auto && f, const std::vector<T> & vec, Args && ... args) {
		using R = decltype(f(std::declval<T>(), (std::declval<Args>())...));
		std::vector<R> results;
		for(const auto & elem : vec) results.push_back(f(elem, args...));
		return results;
	}

	constexpr auto mapped(auto && f) {
		return [f] (const auto & collection, auto && ... args) {
			return map(f, collection, args...); 
		};
	}
}