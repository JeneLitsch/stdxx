#pragma once
#include <iterator>
#include <cmath>
#include "../concepts.hxx"

namespace stx {
	template<typename AB, typename T>
	AB lerp(const AB & a, const AB & b, const T & t);


	namespace internal {
		auto lerp_impl(
			std::floating_point auto a,
			std::floating_point auto b,
			std::floating_point auto t) {
			
			using T = decltype((a + b) * t);
			
			return static_cast<T>(a) + t * static_cast<T>(b - a);
		}


		auto lerp_impl(
			std::unsigned_integral auto a,
			std::unsigned_integral auto b,
			std::floating_point auto t) {
			
			using T = decltype((a + b) * t);
			
			const auto l = static_cast<T>(std::min(a, b));
			const auto h = static_cast<T>(std::max(a, b));
			const auto x = static_cast<T>(a < b ? t : 1-t);
			return l + x * (h - l);
		}



		auto lerp_impl(
			std::signed_integral auto a,
			std::signed_integral auto b,
			std::floating_point auto t) {
			
			using T = decltype((a + b) * t);

			return static_cast<T>(a) + t * static_cast<T>(b - a);
		}



		template<typename T, typename Flavor>
		auto lerp_impl(
			const vector2<T, Flavor> & a,
			const vector2<T, Flavor> & b,
			auto t) {
			
			const auto x = stx::lerp(a.x, b.x, t);
			const auto y = stx::lerp(a.y, b.y, t);
			return vector2<T, Flavor> {x, y};
		}



		template<typename T, typename Flavor>
		auto lerp_impl(
			const vector3<T, Flavor> & a,
			const vector3<T, Flavor> & b,
			auto t) {
			
			const auto x = stx::lerp(a.x, b.x, t);
			const auto y = stx::lerp(a.y, b.y, t);
			const auto z = stx::lerp(a.z, b.z, t);
			return vector3<T, Flavor> {x, y, z};
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
	}



	template<typename AB, typename T>
	AB lerp(const AB & a, const AB & b, const T & t) {
		return static_cast<AB>(internal::lerp_impl(a, b, t));
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