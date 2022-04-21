#pragma once
#include "node.hxx"
#include <ostream>
#include <iomanip>
#include "../io/escaped.hxx"

namespace stx::json {
	std::ostream & operator<<(std::ostream & out, const node & n);
	struct Printer {
		std::ostream & out;



		void operator()(std::monostate) {
			out << "null";
		}



		void operator()(double value) {
			out << std::setprecision(10) << value;
		}



		void operator()(bool value) {
			out << std::boolalpha << value;
		}



		void operator()(const std::string & value) {
			out << escaped(value);
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