#pragma once
#include <functional>
#include "functional/fx_ptr.hxx"
#include "functional/map.hxx"

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


	template<typename R, typename T>
	using unary = std::function<R(T)>;

	using runnable = std::function<void(void)>;

	template<typename T>
	using consumer = std::function<void(T)>;

	template<typename T>
	using provider = std::function<T(void)>;

	template<typename ... T>
	using predicate = std::function<bool(T...)>;
}