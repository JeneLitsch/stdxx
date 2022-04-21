#pragma once
#include "node.hxx"
namespace stx::json {
	class iterator {
	public:
		iterator(const node * node) : n(node) {}
		
		bool null() const {
			if(!n) return false;
			return std::get_if<std::monostate>(&n->data);
		}

		operator bool() const {
			return n;
		}

		const double * number() const {
			if(!n) return nullptr;
			return std::get_if<double>(&n->data);
		}
		
		const bool * boolean() const {
			if(!n) return nullptr;
			return std::get_if<bool>(&n->data);
		}

		const std::string * string() const {
			if(!n) return nullptr;
			return std::get_if<std::string>(&n->data);
		}

		const std::vector<node> * array() const {
			if(!n) return nullptr;
			return std::get_if<std::vector<node>>(&n->data);
		}

		const std::vector<std::pair<std::string, node>> * object() const {
			if(!n) return nullptr;
			return std::get_if<std::vector<std::pair<std::string, node>>>(&n->data);
		}

		iterator operator[](std::size_t i) const {
			if(!n) {
				return iterator(nullptr);
			}
			if(i >= this->size()) {
				return iterator(nullptr);
			}
			auto * arr = this->array();
			auto * elem = &(*arr)[i];
			return iterator(elem);
		}


		iterator operator[](std::integral auto i) const {
			return this->operator[](static_cast<std::size_t>(i));
		}

		iterator operator[](const std::string & str) const {
			if(!n) {
				return iterator(nullptr);
			}
			if(auto * arr = this->object()) {
				for(const auto & [key, value] : *arr) {
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
			if(auto arr = this->array()) {
				return arr->size();
			}
			return 0;
		}
	private:
		const node * n;
		inline static const std::vector<node> empty;
	};
}