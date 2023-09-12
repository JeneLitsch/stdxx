#pragma once
#include "node.hxx"
#include <ostream>
#include <iomanip>
#include "../io/escaped.hxx"
#include <array>

namespace stx::json {
	struct style {
		bool use_newlines = false;
		bool use_indent = true;
	};



	inline style compact {
		.use_newlines = false,
		.use_indent = false,
	};



	inline style pretty {
		.use_newlines = true,
		.use_indent = true,
	};



	namespace do_not_touch {
		void print_node(
			std::ostream & out,
			const node & node,
			int indentation,
			const style & style);


		
		inline void print_newline(
			std::ostream & out,
			const style & style) {
			out << (style.use_newlines ? "\n" : "");
		}



		inline void print_indent(
			std::ostream & out,
			int indentation,
			const style & style) {
			auto indent_depth = static_cast<std::size_t>(std::max(indentation, 0));
			out << (style.use_indent ? std::string(indent_depth, '\t') : "");
		}



		inline void print(
			std::ostream & out,
			std::monostate,
			[[maybe_unused]] int indentation,
			[[maybe_unused]] const style & style) {
			out << "null";
		}



		inline void print(
			std::ostream & out,
			double value,
			[[maybe_unused]] int indentation,
			[[maybe_unused]] const style & style) {
			out << std::setprecision(10) << value;
		}



		inline void print(
			std::ostream & out,
			bool value,
			[[maybe_unused]] int indentation,
			[[maybe_unused]] const style & style) {
			out << std::boolalpha << value;
		}



		inline void print(
			std::ostream & out,
			const std::string & value,
			[[maybe_unused]] int indentation,
			[[maybe_unused]] const style & style) {
			out << escaped(value);
		}




		inline void print_list(
			std::ostream & out,
			const auto & list,
			int indentation,
			const style & style,
			std::array<char, 2> parens,
			const auto & fx) {
			
			out << parens[0];
			bool first = true;
			for(const auto & elem : list) {
				if(first) {
					first = false;
				} 
				else {
					out << ",";
				}
				print_newline(out, style);
				print_indent(out, indentation+1, style);
				fx(elem, indentation+1);
			}
			print_newline(out, style);
			print_indent(out, indentation, style);
			out << parens[1];
		}



		inline void print(
			std::ostream & out,
			const std::vector<node> & nodes,
			int indentation,
			const style & style) {
			print_list(out, nodes, indentation, style, {'[',']'}, [&] (const auto & n, int indentation) {
				print_node(out, n, indentation, style);
			});
		}



		inline void print(
			std::ostream & out,
			const std::vector<std::pair<std::string, node>> & dict,
			int indentation,
			const style & style) {
			
			print_list(out, dict, indentation, style, {'{','}'}, [&] (const auto & pair, int indentation) {
				const auto & [key, node] = pair;
				out << '"' << key << '"' << ':';
				print_node(out, node, indentation, style);
			});
		}



		inline void print_node(
			std::ostream & out,
			const node & node,
			int indentation,
			const style & style) {
			std::visit([&](auto x) { do_not_touch::print(out, x, indentation, style); }, node.data);
		}
	}



	struct format_t {
		const node * node;
		style style;
	};



	inline format_t format(const node & node, const style & style) {
		return format_t {
			.node = &node,
			.style = style
		};
	}



	inline format_t format(node && node, const style & style) = delete;



	inline std::ostream & operator<<(std::ostream & out, format_t format) {
		do_not_touch::print_node(out, *format.node, 0, format.style);
		return out;
	}



	inline std::ostream & operator<<(std::ostream & out, const node & n) {
		out << format(n, compact);
		return out;
	}
}