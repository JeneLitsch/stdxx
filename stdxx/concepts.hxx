#pragma once
#include <concepts>
#include <cmath>

namespace stx {
	
	template<typename Color>
	concept color_rgba = requires(Color c) {
		Color{c.r, c.g, c.b, c.a};
	};



	template<typename Color>
	concept color_rgb = requires(Color c) { 
		Color{c.r, c.g, c.b};
	} && !color_rgba<Color>;



	template<typename Vector3>
	concept vector_3 = requires(Vector3 v) {
		Vector3{v.x, v.y, v.z};
	};



	template<typename Vector2> 
	concept vector_2 = requires(Vector2 v) {
		Vector2{v.x, v.y};
	} && !vector_3<Vector2>;



	template<typename T>
	concept default_lerpable = requires(T a, T b) {
		a + 0.5 * (b - 0.5);
	};



	template<typename Arr>
	concept ranged_array = requires(Arr arr) {
		arr.begin();
		arr.end();
	};



	template<typename T, typename Fx>
	concept binary_fx = requires(Fx fx, T x, T y) {
		std::same_as<decltype(fx(x, y)), T>;
	};



	template<typename T>
	concept string_like = std::is_convertible_v<T, std::string_view>;
}