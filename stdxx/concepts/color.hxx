#pragma once
#include <type_traits>

namespace stx {
	template<typename Color>
	concept color_rgba = requires(Color c) {
		Color{c.r, c.g, c.b, c.a};
	};



	template<typename Color>
	concept color_rgb = requires(Color c) { 
		Color{c.r, c.g, c.b};
	};



	template<typename Color>
	concept color_rgb_no_alpha = color_rgb<Color> && !color_rgba<Color>;
}