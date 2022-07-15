#pragma once
#include "stdxx/args/option.hxx"
#include "stdxx/args/read_from_stream.hxx"

namespace stx {
	template<typename T>
	class basic_option_list final : public option {
	public:
		basic_option_list(
			const std::vector<std::string> & names,
			const std::string & title,
			const std::string & descr) : 
			option { names, title, descr } {}

		basic_option_list(
			const std::string & name,
			const std::string & title,
			const std::string & descr) : 
			basic_option_list { std::vector{name}, title, descr } {}

		basic_option_list(const basic_option_list &) = default; 
		basic_option_list(basic_option_list &&) = default; 
		basic_option_list & operator=(const basic_option_list &) = default; 
		basic_option_list & operator=(basic_option_list &&) = default; 
		
		virtual bool parse(const std::string_view & name, std::istream & in) override {
			if(!this->matches(name)) return false;
			this->set = true;
			int c = (in >> std::ws).peek();
			while (c != '-' && c != EOF) {
				array.push_back({});
				internal::read_from_stream(array.back(), in);
				if(!in) throw std::runtime_error {
					"Invalid element in option list " + this->get_main_name()
				};
				c = (in >> std::ws).peek();
			}
			return true;
		}

		virtual void mandatory() const override {
			if(!this->set || this->array.empty()) throw std::runtime_error {
				this->get_main_name() + " is a mandatory option."
			};
		}

		const std::vector<T> get() const {
			return this->array;
		}

		bool is_set() const {
			return this->set;
		}
	private:
		bool set = false;
		std::vector<T> array;
	};

	using option_bool_list = basic_option_list<bool>;
	using option_int_list = basic_option_list<int>;
	using option_long_list = basic_option_list<long>;
	using option_float_list = basic_option_list<float>;
	using option_double_list = basic_option_list<double>;
	using option_string_list = basic_option_list<std::string>;
}