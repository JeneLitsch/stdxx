#pragma once
#include <stdexcept>
namespace stx::json {
	
	// General json related error
	struct error : std::runtime_error {
		error(const auto & msg) 
			: std::runtime_error(msg) {}
	};

	// Error while parsing file
	struct syntax_error : stx::json::error {
		syntax_error(const auto & msg) 
			: error(msg) {}
	};

	// Error while reading data from parsed json
	struct format_error : stx::json::error {
		format_error(const auto & msg) 
			: error(msg) {}
	};
}