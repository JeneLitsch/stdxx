#pragma once
#include <tuple>
#include <chrono>

#include "chrono/Clock.hxx"
#include "chrono/every.hxx"

namespace stx::chrono {
	inline std::tuple<std::chrono::hours, std::chrono::minutes, std::chrono::seconds> split_hh_mm_ss(std::chrono::seconds t) {
		return {
			std::chrono::duration_cast<std::chrono::hours>  (t),
			std::chrono::duration_cast<std::chrono::minutes>(t) % 60,
			std::chrono::duration_cast<std::chrono::seconds>(t) % 60,
		};
	}

	using seconds_d = std::chrono::duration<double>;
}