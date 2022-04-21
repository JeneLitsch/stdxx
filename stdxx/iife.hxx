#pragma once

constexpr auto iife(const auto & callable) {
	return callable();
}



namespace stx {
	constexpr inline auto iife = [](const auto & callable) {
		return ::iife(callable);
	};
}