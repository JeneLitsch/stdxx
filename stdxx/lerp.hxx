#pragma once
#include <iterator>
#include <cmath>
#include "concepts.hxx"

namespace stx {
	auto lerp(auto a, auto b, auto t) {
		return std::lerp(a, b, t);
	}

	auto lerp(
		const color_rgb auto & c1,
		const color_rgb auto & c2,
		auto t) {
		const auto r = static_cast<std::uint8_t>(std::lerp(c1.r, c2.r, t));
		const auto g = static_cast<std::uint8_t>(std::lerp(c1.g, c2.g, t));
		const auto b = static_cast<std::uint8_t>(std::lerp(c1.b, c2.b, t));
		return decltype(c1){r, g, b};
	}

	auto lerp(
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