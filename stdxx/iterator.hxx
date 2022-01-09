#pragma once
#include "iterator_range.hxx"
namespace stx {

	auto size(const auto begin, const auto end) {
		return std::distance(begin, end);
	}

	bool empty(const auto begin, const auto end) {
		return stx::size(begin, end) == 0;
	}

	constexpr auto whole(auto & container) {
		auto begin = container.begin();
		auto end = container.end();
		using It = decltype(begin);
		return iterator_range<It>{begin, end};
	}

	constexpr auto first_n(auto & container, std::size_t n) {
		auto begin = container.begin();
		auto end = container.end();
		auto plus_n = container.begin();

		using It = decltype(begin);
	
		for(std::size_t i = 0; i < n;  i++) {
			if(plus_n == end) {
				return iterator_range<It>{begin, end};
			}
			plus_n = std::next(plus_n);
		}
	
		return iterator_range<It>{begin, plus_n};
	}

	constexpr auto last_n(auto & container, std::size_t n) {
		auto begin = container.begin();
		auto end = container.end();
		auto minus_n = container.end();

		using It = decltype(begin);
	
		for(std::size_t i = 0; i < n;  i++) {
			if(minus_n == begin) {
				return iterator_range<It>{begin, end};
			}
			minus_n = std::prev(minus_n);
		}
	
		return iterator_range<It>{minus_n, end};
	}
}