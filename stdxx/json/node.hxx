#pragma once
#include <variant>
#include <vector>
#include <string>
#include <unordered_map>
#include "../concepts.hxx"

namespace stx::json {
	struct node final {
		node(std::nullptr_t = nullptr)
			: data{std::monostate{}} {}
		
		node(bool value)
			: data{value} {}
		
		node(std::floating_point auto value)
			: data{value} {}

		node(std::integral auto value)
			: data{static_cast<double>(value)} {}
		
		node(const stx::string_like auto & value)
			: data{std::string{value}} {}

		node(const std::vector<node> & value)
			: data{value} {}

		node(const std::initializer_list<node> & value)
			: node(std::vector(value)) {}

		node(const std::vector<std::pair<std::string, node>> & value)
			: data{value} {}
		
		node(const std::initializer_list<std::pair<std::string, node>> & value)
			: node(std::vector(value)) {}

		std::variant<
			std::monostate,
			bool,
			double,
			std::string,
			std::vector<node>,
			std::vector<std::pair<std::string, node>>
		> data;
	};
}