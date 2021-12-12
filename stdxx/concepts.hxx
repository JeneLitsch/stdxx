#pragma once
#include <concepts>

namespace cxx {
	template<typename Color>
	concept color_rgb = requires(Color c) { 
		Color{c.r, c.g, c.b};
	};
	
	
	template<typename Color>
	concept color_rgba = requires(Color c) {
		Color{c.r, c.g, c.b, c.a};
	};


	template<typename Vector2> 
	concept vector_2 = requires(Vector2 v) {
		Vector2{v.x, v.y};
	};


	template<typename Vector3>
	concept vector_3 = requires(Vector3 v) {
		Vector3{v.x, v.y, v.z};
	};
}