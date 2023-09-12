#pragma once
#include "node.hxx"
#include "error.hxx"
#include <optional>

namespace stx::json {
	inline const struct null_t {} null;
	inline const struct array_t {} array;
	inline const struct object_t {} object;

	class write_iterator {
		using Object = std::vector<std::pair<std::string, node>>;
		using Array = std::vector<node>;
	public:
		write_iterator(node * node) : n{node} {}
		write_iterator(node & node) : n{&node} {}


		write_iterator & operator=(null_t) {
			this->n->data = std::monostate{};
			return *this;
		}

		write_iterator & operator=(std::nullopt_t) {
			this->n->data = std::monostate{};
			return *this;
		}

		write_iterator & operator=(std::nullptr_t) {
			this->n->data = std::monostate{};
			return *this;
		}

		write_iterator & operator=(bool b) {
			this->n->data = b;
			return *this;
		}

		write_iterator & operator=(std::integral auto i) {
			this->n->data = static_cast<double>(i);
			return *this;
		}

		write_iterator & operator=(std::floating_point auto f) {
			this->n->data = static_cast<double>(f);
			return *this;
		}

		write_iterator & operator=(array_t) {
			this->n->data = Array{};
			return *this;
		}

		write_iterator & operator=(object_t) {
			this->n->data = Object{};
			return *this;
		}

		write_iterator & operator=(const stx::string_like auto & str) {
			this->n->data = std::string{str};
			return *this;
		}

		write_iterator & operator=(node node) {
			*this->n = node;
			return *this;
		}



		write_iterator operator[](std::integral auto index) {
			const auto i = static_cast<std::size_t>(index);
			auto & arr = this->get_array();
			if(arr.size() <= i) arr.resize(i + 1);
			return write_iterator{arr[i]};
		}



		write_iterator operator[](const stx::string_like auto & str) {
			auto & dict = this->get_object();
			for(auto & [key, value] : dict) {
				if(key == str) return write_iterator{value};
			}
			dict.push_back({str, node{}});
			return write_iterator{dict.back().second};
		}



		void push_back(auto x) {
			auto & arr = this->get_array();
			arr.push_back(nullptr);
			auto it = write_iterator{arr.back()};
			it = x;
		}
		
	private:
		Object & get_object() {
			if(!std::holds_alternative<Object>(n->data)) n->data = Object{};
			return std::get<Object>(n->data);
		}

		Array & get_array() {
			if(!std::holds_alternative<Array>(n->data)) n->data = Array{};
			return std::get<Array>(n->data);
		}


		node * n;
	};
}