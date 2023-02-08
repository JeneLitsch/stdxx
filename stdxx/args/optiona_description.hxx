#pragma once
#include <vector>
#include <sstream>
#include <ostream>
#include <set>
#include <iterator>
#include "stdxx/memory.hxx"
#include "stdxx/algorithm.hxx"
#include "stdxx/iterator.hxx"
#include "stdxx/io.hxx"
#include "stdxx/args/option.hxx"
#include "stdxx/args/args.hxx"

namespace stx {
	class option_description {
	public:
		option_description(
			const std::string & program_name,
			const std::string & overview) :
			program_name { program_name },
			overview { overview } {}

		template<typename T>
		T & add(
			const std::string & name,
			const std::string & title,
			const std::string & descr,
			const auto & ... args) {
			
			return this->add<T>(std::vector<std::string>{name}, title, descr, args...);
		}

		template<typename T>
		T & add(const std::vector<std::string> & names,
			const std::string & title,
			const std::string & descr,
			const auto & ... args) {
			
			auto option = stx::make_unique<T>(names, title, descr, args...);
			auto & ref = *option;
			this->options.push_back(std::move(option));
			return ref;
		}

		template<typename T>
		T & add(
			const std::initializer_list<std::string> & names,
			const std::string & title,
			const std::string & descr,
			const auto & ... args) {
			return this->add<T>(std::vector<std::string>{names}, title, descr, args...);
		}


		std::string describe() const {
			std::ostringstream oss;

			oss	
				<< this->program_name << "\n\n";

			oss 
				<< "Overview:\n"
				<< "  " << this->overview << "\n\n";
			
			oss
				<< "Options:\n";
			for(const auto & option : this->options) {
				oss
					<< "  " << option->get_title() << " "
					<< "["  << stx::separated(option->get_all_names(), ", ") << "]" << "\n"
					<< "     " << option->get_descr() << "\n"
					<< "\n";
			}
			return oss.str();
		}


		args::iterator parse(args & args) {
			auto [begin, end] = stx::whole(this->options);

			static constexpr auto fetch = [] (std::istream & in) {
				std::string str;
				if(!in.eof()) in >> str;
				return str;
			};

			static constexpr auto fetch_first = [] (std::istream & in) {
				while(true) {
					const auto str = fetch(in);
					if(str.empty() || str[0] == '-') return str;
				}
			};

			auto it = args.iter();
			while(it.is_flag()) {
				const auto arg = it.str();
				if(arg == "--") return ++it;
				++it;
				bool invalid_option = none_of_short_ciruit(begin, end, [&] (auto & option) {
					return option->parse(arg, it); 
				});

				if(invalid_option) throw std::runtime_error {
					"Unkown option " + arg
				};
			};
			return it;
		} 
	private:
		std::vector<std::unique_ptr<option>> options;
		std::string program_name;
		std::string overview;
	};
}