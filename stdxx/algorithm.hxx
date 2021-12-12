#pragma once

namespace stx {
	template<class Iterator, class RandomGenerator>
	Iterator select_random(Iterator begin, Iterator end, RandomGenerator & random) {
		const auto size = std::distance(begin, end);
		if(size == 0) {
			return end;
		}
		std::uniform_int_distribution<> dist(0, static_cast<int>(size - 1U));
		const auto idx = dist(random);
		std::advance(begin, idx);
		return begin;
	}
}
