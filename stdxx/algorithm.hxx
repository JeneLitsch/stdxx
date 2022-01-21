#pragma once
#include "iterator.hxx"

namespace stx {
	// Returns a random iterator in range [begin, end)
	// Return end if the range is empty (distance <= 0).
	auto select_random(auto begin, auto end, auto & rng) {
		const auto size = stx::size(begin, end);
		if(size <= 0) {
			return end;
		}
		std::uniform_int_distribution<> dist(0, static_cast<int>(size - 1U));
		const auto idx = dist(rng);
		std::advance(begin, idx);
		return begin;
	}

	void for_each_if(auto begin, auto end, auto pred, auto op) {
		std::for_each(begin, end, [pred, op] (auto & elem) {
			if(pred(elem)) op(elem);
		});
	}
}
