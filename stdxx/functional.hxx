#pragma once

namespace stx {
	constexpr auto deref(auto & ptr_like) {
		return *ptr_like;
	}

	constexpr auto before(auto main_fx, auto called_before) {
		return [main_fx, called_before] (auto & param) {
			return main_fx(called_before(param));
		};
	}

	// For predicate functions: Derefs the single parameter
	// Allows to use algorithms on containers with pointer types.
	// e.g. std::vector<std::unique_ptr<?>>
	constexpr auto deref_parameter(auto fx) {
		return [fx] (auto & ptr) { return fx(*ptr); };
	}
}