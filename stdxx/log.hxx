#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <sstream>

namespace stx {
	struct log_level {
		std::string_view tag;
	};

	constexpr auto FATAL   = log_level { "[Fatal] " };
	constexpr auto ERROR   = log_level { "[Error] " };
	constexpr auto WARNING = log_level { "[Warning] " };
	constexpr auto INFO    = log_level { "[Info] " };
	constexpr auto WRITE   = log_level { "" };
	
	inline class logger {
		template<typename Type>
		class line {
		public:
			line(auto & outs, const Type & type, unsigned indent) : outs(outs) { 
				ss << std::string(indent, '\t') << type.tag;
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

		template<typename Type>
		auto operator[](const Type & type) {
			return line<Type>(outs, type, indentation);
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