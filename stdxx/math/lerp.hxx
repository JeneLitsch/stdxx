#pragma once
#include <iterator>
#include <cmath>
#include "../concepts.hxx"

namespace stx {
	template<std::signed_integral I, std::floating_point T>
	I lerp(I a, I b, T t) {
		using X = std::common_type_t<I, T>;
		return static_cast<I>(static_cast<X>(a) + t * static_cast<X>(b - a));
	}


	template<std::unsigned_integral U, std::floating_point T>
	U lerp(U a, U b, T t) {		
		using X = std::common_type_t<U, T>;
		const auto l = static_cast<X>(std::min(a, b));
		const auto h = static_cast<X>(std::max(a, b));
		const auto x = static_cast<X>(a < b ? t : 1-t);
		return static_cast<U>(l + x * (h - l));
	}



	template<std::floating_point F, std::floating_point T>
	F lerp(F a, F b, T t) {
		using X = std::common_type_t<F, T>;
		return static_cast<F>(static_cast<X>(a) + t * static_cast<X>(b - a));
	}



	template<vector_2 Vec2, std::floating_point T>
	Vec2 lerp(const Vec2 & a, const Vec2 & b, T t) {
		const auto x = stx::lerp(a.x, b.x, t);
		const auto y = stx::lerp(a.y, b.y, t);
		return Vec2 {x, y};
	}



	template<vector_3 Vec3 , std::floating_point T>
	Vec3 lerp(const Vec3 & a, const Vec3 & b, T t) {
		const auto x = stx::lerp(a.x, b.x, t);
		const auto y = stx::lerp(a.y, b.y, t);
		const auto z = stx::lerp(a.z, b.z, t);
		return Vec3 {x, y, z};
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



	template<typename T, std::floating_point F>
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