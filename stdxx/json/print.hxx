#pragma once
#include "node.hxx"
#include <ostream>
namespace stx::json {
	std::ostream & operator<<(std::ostream & out, const node & n);
	struct Printer {
		std::ostream & out;

		void operator()(std::monostate) {
			out << "null";
		}

		void operator()(double value) {
			out << value;
		}

		void operator()(bool value) {
			out << value;
		}

		void operator()(const std::string & value) {
			out << '"';
			for(const char c : value) {
				switch (c) {
				case '\n': out << "\\n"; break;
				case '\t': out << "\\t"; break;
				case '\"': out << "\\\""; break;
				case '\\': out << "\\\\"; break;				
				default: out << c;
				}
			}
			out << '"';
		}

		void operator()(const std::vector<node> & nodes) {
			out << "[";
			bool first = true;
			for(const auto & n : nodes) {
				if(!first) out << ", ";
				if(first) first = false;
				out << n;
			}
			out << "]";
		}

		void operator()(const std::vector<std::pair<std::string, node>> & dict) {
			out << "{";
			bool first = true;
			for(const auto & [key, n] : dict) {
				if(!first) out << ", ";
				if(first) first = false;
				out << '"' << key << '"' << ':' << n; 
			}
			out << "}";
		}
	};
	
	std::ostream & operator<<(std::ostream & out, const node & n) {
		Printer printer{out};
		std::visit(printer, n.data);
		return out;
	}
}