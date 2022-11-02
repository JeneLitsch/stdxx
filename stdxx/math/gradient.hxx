#pragma once
#include "lerp.hxx"

namespace stx {
    auto gradient(
		std::input_iterator auto begin,
		std::input_iterator auto end,
		std::floating_point auto t) {
		
		using R = std::remove_reference_t<decltype(*begin)>;

		auto size = std::distance(begin, end);	
		
		if(t < 0) {
			return static_cast<R>(*begin);
		}
		if(t >= static_cast<decltype(t)>(size)) {
			return static_cast<R>(*(end - 1));
		} 
		auto prev = begin + static_cast<unsigned>(std::floor(t));
		auto next = begin + static_cast<unsigned>(std::ceil(t));
		auto t_ = std::fmod(t, 1);
		auto result = stx::lerp(*prev, *next, t_);
		return static_cast<R>(result);
	}
}