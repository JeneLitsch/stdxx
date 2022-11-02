#pragma once
#include <iterator>
#include <cmath>
#include "../concepts.hxx"

namespace stx {
	template<typename T>
	concept default_lerpable = requires(T a, T b) {
		a + 0.5 * (b - a);
	};


	auto lerp(default_lerpable auto a, default_lerpable auto b, std::floating_point auto t) {
		using T = decltype(a + (b - a) * t);
		return static_cast<decltype(a+b)>(static_cast<T>(a) + t * (static_cast<T>(b) - static_cast<T>(a)));
	}



	auto lerp(const color_rgb_no_alpha auto & c1, const color_rgb_no_alpha auto & c2,	auto t) {
		const auto r = static_cast<std::uint8_t>(std::lerp(c1.r, c2.r, t));
		const auto g = static_cast<std::uint8_t>(std::lerp(c1.g, c2.g, t));
		const auto b = static_cast<std::uint8_t>(std::lerp(c1.b, c2.b, t));
		return decltype(c1){r, g, b};
	}



	auto lerp(const color_rgba auto & c1, const color_rgba auto & c2, auto t) {
		const auto r = static_cast<std::uint8_t>(std::lerp(c1.r, c2.r, t));
		const auto g = static_cast<std::uint8_t>(std::lerp(c1.g, c2.g, t));
		const auto b = static_cast<std::uint8_t>(std::lerp(c1.b, c2.b, t));
		const auto a = static_cast<std::uint8_t>(std::lerp(c1.a, c2.a, t));
		return decltype(c1){r, g, b, a};
	}



	auto lerp(const vector_2 auto & v1, const vector_2 auto & v2, auto t) {
		const auto x = lerp(v1.x, v2.x, t);
		const auto y = lerp(v1.y, v2.y, t);
		return decltype(v1) {x, y};
	}



	auto lerp(const vector_3 auto & v1, const vector_3 auto & v2, auto t) {
		const auto x = lerp(v1.x, v2.x, t);
		const auto y = lerp(v1.y, v2.y, t);
		const auto z = lerp(v1.z, v2.z, t);
		return decltype(v1) {x, y, z};
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



	template<std::floating_point F, typename T>
	auto bi_lerp(T nw, T ne, T sw, T se, F tx, F ty) {
		return stx::lerp(
			stx::lerp(nw, ne, tx),
			stx::lerp(sw, se, tx),
			ty
		);
	}


	template<std::floating_point F = float>
	F progress(auto val, auto min, auto max) {
		const auto relative = static_cast<F>(val - min);
		const auto distance = static_cast<F>(max - min);  
		return relative / distance;
	}	
}