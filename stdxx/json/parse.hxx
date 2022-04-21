#pragma once
#include "node.hxx"
#include <istream>
#include <iostream>
#include "../io/escaped.hxx"

namespace stx::json {
	namespace do_not_touch {
		node parse(std::istream & in);


		inline bool match(std::istream & in, char c) {
			in >> std::ws;
			if(in.peek() == c) {
				in.ignore();
				return true;
			}
			return false;
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
			if(in.fail()) throw std::runtime_error{"Invalid string literal"};
			return str;
		}



		inline double parse_number(std::istream & in) {
			double num;
			in >> std::ws >> num;
			if(in.fail()) throw std::runtime_error{"Invalid Number literal"};
			return num;
		}



		inline auto parse_collection(std::istream & in, char begin, char end, auto fx_elem) {
			std::vector<decltype(fx_elem(in))> arr;
			
			if(!match(in, begin)) throw std::runtime_error {
				std::string("Must begin with ") + begin
			};
			
			if(match(in, end)) return arr;

			else while (true) {
				arr.push_back(fx_elem(in));
				
				if(in.eof()) throw std::runtime_error {
					"Unterminated"
				};
				
				if(match(in, end)) return arr;
				
				if(!match(in, ',')) throw std::runtime_error {
					"Expected comma between elements"
				};
			}
		}



		inline auto parse_array(std::istream & in) {
			return parse_collection(in, '[', ']', parse);
		}



		inline auto parse_entry(std::istream & in) {
			std::string key = parse_string(in);
			if(!match(in, ':')) {
				throw std::runtime_error("Expected : between and value");
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

			throw std::runtime_error{"Invalid json node"};
		}
	}



	std::istream & operator>>(std::istream & in, node & node) {
		node = do_not_touch::parse(in);
		return in;
	}
}