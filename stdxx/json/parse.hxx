#pragma once
#include <istream>
#include <iostream>
#include <optional>

#include "node.hxx"
#include "error.hxx"

#include "../io/escaped.hxx"

namespace stx::json {
	namespace impl {
		node parse(std::istream & in);

		

		inline std::optional<char> match(std::istream & in, auto predicate) {
			const int c = in.peek();  
			if(predicate(c)) {
				in.ignore();
				return static_cast<char>(c);
			}
			return std::nullopt;
		}
		


		inline std::optional<char> match(std::istream & in, char c1) {
			return match(in, [c1] (auto c2) { return c1 == c2; });
		}



		inline std::optional<char> match_digit(std::istream & in) {
			return match(in, [] (auto c) { return std::isdigit(c); });
		}



		inline bool match_ws(std::istream & in, char c) {
			return match(in >> std::ws, c).has_value();
		}

		
		
		inline auto keyword(std::istream & in) {
			std::string str;
			while(true) {
				const int c = in.peek();
				if(std::isalpha(c)) {
					str.push_back(static_cast<char>(c));
					in.ignore();
				}
				else return str;
			}
		}



		inline std::string parse_string(std::istream & in) {
			std::string str;
			in >> std::ws >> escaped(str);
			if(in.fail()) throw syntax_error{
				"Invalid string literal"
			};
			return str;
		}



		inline double parse_number(std::istream & in) {
			std::stringstream ss;
			
			// Sign			
			if(auto sign = match(in, '-')) {
				ss << *sign;
			}

			// Integer
			if(auto first = match_digit(in)) {
				ss << *first;
				if(first == '0') {}
				else {
					while(auto digit = match_digit(in)) {
						ss << *digit;
					}
				}
			}
			else {
				throw syntax_error{"Expected digit"};
			}
			
			
			// Fraction
			if(auto dot = match(in, '.')) {
				ss << *dot;
				if(auto first = match_digit(in)) {
					ss << *first;
					while(auto digit = match_digit(in)) {
						ss << *digit;
					}
				}
				else {
					throw syntax_error{"Expected digit"};
				}
			}


			// Exponent

			if((in.peek() == 'E') || (in.peek() == 'e')) {
				ss << static_cast<char>(in.get());

				if((in.peek() == '+') || (in.peek() == '-')) {
					ss << static_cast<char>(in.get());
				}

				if(auto first = match_digit(in)) {
					ss << *first;
					while(auto digit = match_digit(in)) {
						ss << *digit;
					}
				}
				else {
					throw syntax_error{"Expected digit"};
				}
			}

			double num;
			ss >> num;
			if(ss.fail()) throw syntax_error{
				"Invalid Number literal"
			};
			return num;
		}



		inline auto parse_collection(std::istream & in, char begin, char end, auto fx_elem) {
			std::vector<decltype(fx_elem(in))> arr;
			
			if(!match_ws(in, begin)) throw syntax_error {
				std::string("Must begin with ") + begin
			};
			
			if(match_ws(in, end)) return arr;

			else while (true) {
				arr.push_back(fx_elem(in));
				
				if(in.eof()) throw syntax_error {
					"Unterminated"
				};
				
				if(match_ws(in, end)) return arr;
				
				if(!match_ws(in, ',')) throw syntax_error {
					"Expected comma between elements"
				};
			}
		}



		inline auto parse_array(std::istream & in) {
			return parse_collection(in, '[', ']', parse);
		}



		inline auto parse_entry(std::istream & in) {
			std::string key = parse_string(in);
			if(!match_ws(in, ':')) {
				throw syntax_error("Expected : between and value");
			}
			return std::pair{key, parse(in)};
		}


		inline auto parse_object(std::istream & in) {
			return parse_collection(in, '{', '}', parse_entry);
		}



		inline node parse(std::istream & in)  {
			in >> std::ws;

			const int c = in.peek();
			if(c == '"')        return node(parse_string(in));
			if(c == '-')        return node(parse_number(in));
			if(std::isdigit(c)) return node(parse_number(in));
			if(c == '[') 	    return node(parse_array(in));
			if(c == '{') 		return node(parse_object(in));

			const auto str = keyword(in);
			if(str == "true")   return node(true);
			if(str == "false")  return node(false);
			if(str == "null")   return node(nullptr);

			throw syntax_error{"Invalid json node"};
		}
	}



	inline std::istream & operator>>(std::istream & in, node & node) {
		node = impl::parse(in);
		if(in.get() != EOF) {
			throw syntax_error{"Expected EOF"};
		}
		return in;
	}
}