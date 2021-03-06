#pragma once
#include <cstring>
#include <memory>
namespace stx {

	template<class To, class From>
	To * as(From & from) {
		return dynamic_cast<To*>(&from);
	}


	template <class Dest, class Src>
	Dest bitcast(const Src & source) {
		static_assert(sizeof(Src) == sizeof(Dest));
		static_assert(std::is_trivially_copyable_v<Src>);
		static_assert(std::is_trivially_copyable_v<Dest>);
		static_assert(std::is_trivially_constructible_v<Dest>);
		Dest dest;
		std::memcpy(&dest, &source, sizeof(Dest));
		return dest;
	}
}
