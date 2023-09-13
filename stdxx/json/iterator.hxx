#pragma once
#include <cstdint>
#include "node.hxx"
#include "error.hxx"
#include "../optional.hxx"

namespace stx::json {
	class iterator {
		inline static constexpr auto not_a_boolean = "Cannot extract boolean";
		inline static constexpr auto not_a_number  = "Cannot extract number";
		inline static constexpr auto not_a_string  = "Cannot extract string";
		
		using Dict = std::vector<std::pair<std::string, node>>;
	public:

		iterator(std::nullptr_t) : n(nullptr) {}
		iterator(std::nullopt_t) : n(nullptr) {}
		iterator(const node * node) : n(node) {}
		iterator(const node & node) : n(&node) {}
		
		// Member functions

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
			return ptr_to_opt(std::get_if<bool>(&n->data));
		}

		std::optional<double> number() const {
			if(!n) return std::nullopt;
			return ptr_to_opt(std::get_if<double>(&n->data));
		}

		std::optional<std::string> string() const {
			if(!n) return std::nullopt;
			return ptr_to_opt(std::get_if<std::string>(&n->data));
		}



		std::optional<std::uint8_t> u8() const {
			return static_opt_cast<std::uint8_t>(this->number());
		}

		std::optional<std::int8_t> i8() const {
			return static_opt_cast<std::int8_t>(this->number());
		}

		std::optional<std::uint16_t> u16() const {
			return static_opt_cast<std::uint16_t>(this->number());
		}

		std::optional<std::int16_t> i16() const {
			return static_opt_cast<std::int16_t>(this->number());
		}

		std::optional<std::uint32_t> u32() const {
			return static_opt_cast<std::uint32_t>(this->number());
		}

		std::optional<std::int32_t> i32() const {
			return static_opt_cast<std::int32_t>(this->number());
		}

		std::optional<std::uint64_t> u64() const {
			return static_opt_cast<std::uint64_t>(this->number());
		}

		std::optional<std::int64_t> i64() const {
			return static_opt_cast<std::int64_t>(this->number());
		}



		std::size_t size() const {
			if(!n) return 0;
			if(auto arr = std::get_if<std::vector<node>>(&n->data)) {
				return arr->size();
			}
			return 0;
		}


		std::vector<std::string> keys() const {
			std::vector<std::string> key_vec;
			if(auto * dict = std::get_if<Dict>(&n->data)) {
				for(const auto & [key, value] : *dict) {
					key_vec.push_back(key);
				}
			}
			return key_vec;
		}


		// Operators

		operator bool() const {
			return n;
		}



		iterator operator[](const std::integral auto index) const {
			const auto i = static_cast<std::size_t>(index);
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



		iterator operator[](const stx::string_like auto str) const {
			if(!n) {
				return iterator(nullptr);
			}
			auto * dict = std::get_if<Dict>(&n->data);
			if(dict) {
				for(const auto & [key, value] : *dict) {
					if(key == str) return iterator(&value);
				}
			}
			return iterator(nullptr);
		}


		const node & get_node() const {
			return *n;
		} 

	private:
		const node * n;
	};


	inline auto to_array(stx::json::iterator it) {
		std::vector<stx::json::iterator> arr;
		for(std::size_t i = 0; i < it.size(); i++) {
			arr.push_back(it[i]);
		}
		return arr;
	}
}