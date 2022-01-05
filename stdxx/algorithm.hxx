#pragma once
#include "iterator.hxx"

namespace stx {
	auto select_random(auto begin, auto end, auto & rng) {
		const auto size = std::distance(begin, end);
		if(size == 0) {
			return end;
		}
		std::uniform_int_distribution<> dist(0, static_cast<int>(size - 1U));
		const auto idx = dist(rng);
		std::advance(begin, idx);
		return begin;
	}
}
