#pragma once
#include <string>
#include <sstream>

namespace stx {
	std::string repeat(
		const std::string & str,
		const std::integral auto count) {
		
		std::ostringstream oss;
		for(std::int64_t i = 0; i < count; ++i) {
			oss << str;
		}
		return oss.str();
	}
}