#pragma once
#include <optional>
#include "reference/optref.hxx"
#include "optional/static_opt_cast.hxx"

namespace stx {
	template<typename T>
	constexpr std::optional<T> ptr_to_opt(const T * ptr) {
		if(ptr) return *ptr;
		return std::nullopt;
	}
}