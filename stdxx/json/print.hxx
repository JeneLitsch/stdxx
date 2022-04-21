#pragma once
#include "node.hxx"
#include <ostream>
#include <iomanip>
#include "../io/escaped.hxx"

namespace stx::json {
	std::ostream & operator<<(std::ostream & out, const node & n);

	namespace do_not_touch {
		void print(std::ostream & out, std::monostate) {
			out << "null";
		}



		void print(std::ostream & out, double value) {
			out << std::setprecision(10) << value;
		}



		void print(std::ostream & out, bool value) {
			out << std::boolalpha << value;
		}



		void print(std::ostream & out, const std::string & value) {
			out << escaped(value);
		}



		void print(std::ostream & out, const std::vector<node> & nodes) {
			out << "[";
			bool first = true;
			for(const auto & n : nodes) {
				if(!first) out << ", ";
				if(first) first = false;
				out << n;
			}
			out << "]";
		}



		void print(std::ostream & out, const std::vector<std::pair<std::string, node>> & dict) {
			out << "{";
			bool first = true;
			for(const auto & [key, n] : dict) {
				if(!first) out << ", ";
				if(first) first = false;
				out << '"' << key << '"' << ':' << n; 
			}
			out << "}";
		}
	}

	std::ostream & operator<<(std::ostream & out, const node & n) {
		std::visit([&out](auto x) { do_not_touch::print(out, x); }, n.data);
		return out;
	}
}