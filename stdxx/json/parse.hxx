#pragma once
#include "node.hxx"
#include <istream>
#include <iostream>

namespace stx::json {
	namespace do_not_touch {
		node parse(std::istream & in);
	
		char desecape(char second) {
			if(second == 'n')  return '\n';
			if(second == '"')  return '\"';
			if(second == 't')  return '\t';
			if(second == '\\') return '\\';
			throw std::runtime_error{"Invalid escape sequence"};
		} 


		bool match(std::istream & in, char c) {
			in >> std::ws;
			if(in.peek() == c) {
				in.ignore();
				return true;
			}
			return false;
		}



		std::string parse_string(std::istream & in) {
			if(!match(in, '"')) {
				throw std::runtime_error{
					"String must start with \""};
			}
			std::string str;
			while(true) {
				char c = in.get();
				if(c == '"') break;
				if(c == '\\') c = desecape(in.get());
				str.push_back(c);
			}
			return str;
		}



		double parse_number(std::istream & in) {
			double num;
			in >> num;
			return num;
		}



		std::vector<node> parse_array(std::istream & in) {
			if(!match(in, '[')) {
				throw std::runtime_error("Array mmust begin with [");
			}
			std::vector<node> arr;

			if(match(in, ']')) {
				return arr;
			}
			else while (true) {
				arr.push_back(parse(in));
				if(in.eof()) {
					throw std::runtime_error{
						"Unterminated Array"};
				}
				if(match(in, ']')) return arr;
				if(!match(in, ',')) {
					throw std::runtime_error{
						"Expected comma between elements in array"};
				}
			}
		}



		std::vector<std::pair<std::string, node>>
		parse_object(std::istream & in) {
			std::vector<std::pair<std::string, node>> dict;
		
			if(!match(in, '{')) {
				throw std::runtime_error("Object mmust begin with {");
			}
			if(match(in, '}')) {
				return dict;
			}
			else while (true) {
				std::string key = parse_string(in);
				if(!match(in, ':')) {
					throw std::runtime_error("Expected : between and value");
				}
				dict.push_back({key, parse(in)});
				if(in.eof()) {
					throw std::runtime_error("Unterminated Object");
				}
				if(match(in, '}')) return dict;
				if(!match(in, ',')) {
					std::cerr << in.peek() << "\n"; 
					throw std::runtime_error("Expectd comma between elements in object");
				}
			}
		}



		node parse(std::istream & in)  {
			in >> std::ws;
			char c = in.peek();

			if(c == '"') {
				return node(parse_string(in));
			}
			
			if(std::isdigit(c)) {
				return node(parse_number(in));
			}

			if(c == '[') {
				return node(parse_array(in));
			}

			if(c == '{') {
				return node(parse_object(in));
			}
			
			throw std::runtime_error{"Invalid json node"};
		}

	}

	std::istream & operator>>(std::istream & in, node & node) {
		node = do_not_touch::parse(in);
		return in;
	}
}