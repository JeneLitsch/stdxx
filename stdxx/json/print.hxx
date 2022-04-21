#pragma once
#include "node.hxx"
#include <ostream>
#include <iomanip>
#include "../io/escaped.hxx"

namespace stx::json {
	std::ostream & operator<<(std::ostream & out, const node & n);

	namespace do_not_touch {
		inline void print(std::ostream & out, std::monostate) {
			out << "null";
		}



		inline void print(std::ostream & out, double value) {
			out << std::setprecision(10) << value;
		}



		inline void print(std::ostream & out, bool value) {
			out << std::boolalpha << value;
		}



		inline void print(std::ostream & out, const std::string & value) {
			out << escaped(value);
		}



		inline void print(std::ostream & out, const std::vector<node> & nodes) {
			out << "[";
			bool first = true;
			for(const auto & n : nodes) {
				if(!first) out << ", ";
				if(first) first = false;
				out << n;
			}
			out << "]";
		}



		inline void print(std::ostream & out, const std::vector<std::pair<std::string, node>> & dict) {
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

	inline std::ostream & operator<<(std::ostream & out, const node & n) {
		std::visit([&out](auto x) { do_not_touch::print(out, x); }, n.data);
		return out;
	}
}