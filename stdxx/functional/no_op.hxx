#pragma once

namespace stx {
	inline auto no_op = [] (auto & ...) {};


	constexpr auto always(auto constant) {
		return [constant] (auto & ...) {
			return constant;
		};
	}
}