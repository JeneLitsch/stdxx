#pragma once
#include <optional>

namespace stx {
	template<typename T_OUT, typename T_IN>
	constexpr std::optional<T_OUT> static_opt_cast(const std::optional<T_IN> & opt) {
		if(opt) return static_cast<T_OUT>(*opt);
		else return std::nullopt;
	}



	template<typename T_OUT, typename T_IN>
	constexpr std::optional<T_OUT> static_opt_cast(const T_IN & val) {
		return static_cast<T_OUT>(val);
	}


	
	template<typename T_OUT>
	constexpr std::optional<T_OUT> static_opt_cast(std::nullopt_t) {
		return std::nullopt;
	}
}