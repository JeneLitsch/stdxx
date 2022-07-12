#pragma once
#include <cstring>
#include <array>
#include <string>

namespace stx {
	template<size_t N>
	struct string_literal {
		constexpr string_literal(const char (&str)[N]) 
			: arr(std::to_array(str)) {}



		constexpr const char * c_str() const {
			return arr.data();
		}



		std::string str() const {
			return std::string(this->arr.data());
		}



		constexpr std::size_t size() const {
			return N;
		}



		auto begin() const {
			return this->arr.begin();
		}
		
		auto cbegin() const {
			return this->arr.cbegin();
		}
		
		auto end() const {
			return this->arr.end();
		}
		
		auto cend() const {
			return this->arr.cend();
		}



		constexpr char operator[](std::size_t i) const {
			return this->arr[i];
		}



		operator std::string_view () const {
			return arr.data();
		}



		std::array<char, N> arr;
	};



	template<size_t N>
	inline std::ostream & operator<<(std::ostream & o, const string_literal<N> & str) {
		o << str.c_str();
		return o;
	} 
}