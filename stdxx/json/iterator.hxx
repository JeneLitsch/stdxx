#pragma once
#include "node.hxx"
#include "error.hxx"
#include "../optional.hxx"

namespace stx::json {
	class iterator {
		inline static constexpr auto not_a_boolean = "Cannot extract boolean";
		inline static constexpr auto not_a_number  = "Cannot extract number";
		inline static constexpr auto not_a_string  = "Cannot extract string";
	public:

		iterator(const node * node) : n(node) {}
		iterator(const node & node) : n(&node) {}
		


		operator bool() const {
			return n;
		}



		bool force_boolean(const std::string & error_msg = not_a_boolean) const {
			if(auto val = this->boolean()) return *val;
			throw stx::json::format_error{error_msg};
		}

		double force_number(const std::string & error_msg = not_a_number) const {
			if(auto val = this->number()) return *val;
			throw stx::json::format_error{error_msg};
		}

		std::string force_string(const std::string & error_msg = not_a_string) const {
			if(auto val = this->string()) return *val;
			throw stx::json::format_error{error_msg};
		}



		bool null() const {
			if(!n) return false;
			return std::get_if<std::monostate>(&n->data);
		}

		std::optional<bool> boolean() const {
			if(!n) return std::nullopt;
			return opt_from_ptr(std::get_if<bool>(&n->data));
		}

		std::optional<double> number() const {
			if(!n) return std::nullopt;
			return opt_from_ptr(std::get_if<double>(&n->data));
		}	

		std::optional<std::string> string() const {
			if(!n) return std::nullopt;
			return opt_from_ptr(std::get_if<std::string>(&n->data));
		}





		iterator operator[](std::size_t i) const {
			if(!n) {
				return iterator(nullptr);
			}
			if(i >= this->size()) {
				return iterator(nullptr);
			}
			if(auto arr = std::get_if<std::vector<node>>(&n->data)) {
				auto * elem = &(*arr)[i];
				return iterator(elem);
			} 
			else return nullptr;
		}

		iterator operator[](std::integral auto i) const {
			return this->operator[](static_cast<std::size_t>(i));
		}

		iterator operator[](const std::string & str) const {
			if(!n) {
				return iterator(nullptr);
			}
			using Dict = std::vector<std::pair<std::string, node>>;
			auto * dict = std::get_if<Dict>(&n->data);
			if(dict) {
				for(const auto & [key, value] : *dict) {
					if(key == str) return iterator(&value);
				}
			}
			return iterator(nullptr);
		}

		iterator operator[](const char * str) const {
			return (*this)[std::string(str)];
		}

		iterator operator[](const std::string_view str) const {
			return (*this)[std::string(str)];
		}



		std::size_t size() const {
			if(!n) return 0;
			if(auto arr = std::get_if<std::vector<node>>(&n->data)) {
				return arr->size();
			}
			return 0;
		}

	private:
		const node * n;
		inline static const std::vector<node> empty;
	};


	inline auto to_array(stx::json::iterator it) {
		std::vector<stx::json::iterator> arr;
		for(std::size_t i = 0; i < it.size(); i++) {
			arr.push_back(it[i]);
		}
		return arr;
	}
}