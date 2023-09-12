#pragma once
#include <stdexcept>
#include <filesystem>
#include <fstream>
#include "node.hxx"
#include "parse.hxx"

namespace stx::json {	
	node from_file(auto path) {
		if(!std::filesystem::exists(path)) {
			throw std::runtime_error{
				"No such file exists: " + std::string(path)};
		}
		node n;
		std::ifstream{path} >> n;
		return n;
	}
}