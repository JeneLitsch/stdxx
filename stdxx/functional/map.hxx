#pragma once
#include <vector>

namespace stx::fx {
	template<typename Container, typename ... Args>
	constexpr auto map(auto && f, const Container & container, Args && ... args) {
		using T = typename Container::value_type;
		using R = decltype(f(std::declval<T>(), (std::declval<Args>())...));
		std::vector<R> results;
		for(const auto & elem : container) results.push_back(f(elem, args...));
		return results;
	}

	constexpr auto mapped(auto && f) {
		return [f] (const auto & collection, auto && ... args) {
			return map(f, collection, args...); 
		};
	}
}