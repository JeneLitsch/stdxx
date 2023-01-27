#pragma once

namespace stx::fx {
	constexpr auto paired(auto first_fx, auto second_fx) {
		return [first_fx, second_fx] (const auto & pair) {
			return std::make_pair(first_fx(pair.first), second_fx(pair.second));
		};
	}
}