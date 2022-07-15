#pragma once
#include <istream>
#include <iomanip>

namespace stx::internal {
	inline void read_from_stream(bool & value, std::istream & in) {
		const bool ba = std::isalpha((in >> std::ws).peek());
		in >> (ba ? std::boolalpha : std::noboolalpha) >> value;
	}

	inline void read_from_stream(auto & value, std::istream & in) {
		in >> value;
	}
}