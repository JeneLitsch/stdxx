#pragma once
#include <concepts>

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
}