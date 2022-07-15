#pragma once
#include <vector>
#include <iterator>
#include <string>

namespace stx {
	class option {
	public:
		option(
			const std::vector<std::string> & names,
			const std::string & title,
			const std::string & descr) :
				title { title },
				names { names },
				descr { descr } {
			
			if(std::empty(names)) throw std::runtime_error {
				"Option must have at least one name"
			};

			const bool empty_name = std::any_of(
				std::begin(names),
				std::end(names),
				[](const auto & str) { return std::empty(str); });

			if(empty_name) throw std::runtime_error {
				"Name of option must not be empty!"
			};

			const bool none_dash_name = std::any_of(
				std::begin(names),
				std::end(names),
				[](const auto & str) { return str[0] != '-'; });

			if(none_dash_name) throw std::runtime_error {
				"Name of option must begin with -"
			};				
		}

		const std::string get_title() const {
			return this->title;
		}

		const std::string get_descr() const {
			return this->descr;
		}

		virtual bool parse(const std::string_view & name, std::istream & in) = 0;
		virtual void mandatory() const = 0;

		const std::string & get_main_name() const {
			return this->names[0];
		}

		const std::vector<std::string> & get_all_names() const {
			return this->names;
		}
		virtual ~option() = default;
	protected:
		bool matches(const std::string_view & name) const {
			return std::any_of(
				std::begin(names),
				std::end(names),
				[&] (const auto & str) { return name == str; });
		}

		option(const option &) = default; 
		option(option &&) = default; 
		option & operator=(const option &) = default; 
		option & operator=(option &&) = default;

	private:
		std::string title;
		std::vector<std::string> names;
		std::string descr;
	};
}