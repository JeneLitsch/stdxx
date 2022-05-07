#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <sstream>

namespace stx {

	enum class type {
		FATAL, ERROR, WARNING, INFO, WRITE,
	};

	constexpr auto FATAL = type::FATAL;
	constexpr auto ERROR = type::ERROR;
	constexpr auto WARNING = type::WARNING;
	constexpr auto INFO = type::INFO;
	constexpr auto WRITE = type::WRITE;

	inline std::string_view to_string(type type) {
		switch (type) {
			case type::FATAL:   return "[Fatal] ";   break;
			case type::ERROR:   return "[Error] ";   break;
			case type::WARNING: return "[Warning] "; break;
			case type::INFO:    return "[Info] ";    break;
			case type::WRITE:   return "";           break;
		}
		return "";
	}
	
	inline class logger {
		class line {
		public:
			line(auto & outs, type type, unsigned indent) : outs(outs) { 
				ss << std::string(indent, '\t') << to_string(type);
			}
			line(const line &) = delete;
			line(line &&) = delete;
			line& operator=(const line &) = delete;
			line& operator=(line &&) = delete;
			~line() {
				ss << "\n";
				const auto msg = ss.str(); 
				for(auto out : outs) {
					(*out) << msg << std::flush;
				}
			}
			std::ostream & operator<<(const auto & value) {
				return this->ss << value;
			}
		private:
			std::vector<std::ostream*> & outs; 
			std::stringstream ss;
		};
	public:
		logger() = default;
		logger(const logger &) = delete;
		logger(logger &&) = delete;
		logger operator=(const logger &) = delete;
		logger operator=(logger &&) = delete;

		void register_output(std::ostream & out) {
			outs.push_back(&out);
		}

		auto operator[](type type) {
			return line(outs, type, indentation);
		}

		void indent_in() {
			this->indentation++;
		}

		void indent_out() {
			if(this->indentation) this->indentation--;
		}

		void indent_reset() {
			this->indentation = 0;
		}
	private:
		std::vector<std::ostream*> outs;
		unsigned indentation = {0};
	} log;
}