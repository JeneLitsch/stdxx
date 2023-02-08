#pragma once
#include "stdxx/args/option.hxx"

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
		
		virtual bool parse(const std::string_view & name, args::iterator & it) override {
			if(!this->matches(name)) return false;
			if(!it) return false;
			std::istringstream iss {(it++).str()};
			this->opt_v = std::vector<T>{};
			while (!iss.eof()) {
				T t;
				iss >> t;
				opt_v->push_back(t);
			}
			return true;
		}

		virtual void mandatory() const override {
			if(!this->opt_v) throw std::runtime_error {
				this->get_main_name() + " is a mandatory option."
			};
		}

		const std::vector<T> value() const {
			if(this->opt_v) return *opt_v;
			throw std::runtime_error {
				this->get_main_name() + " is a mandatory option."
			};
		}

		const std::vector<T> value_or(const std::vector<T> & t) const {
			return opt_v.value_or(t);
		}

		operator bool() const {
			return this->opt_v;
		}
	private:
		std::optional<std::vector<T>> opt_v;
	};

	using option_bool_list = basic_option_list<bool>;
	using option_int_list = basic_option_list<int>;
	using option_long_list = basic_option_list<long>;
	using option_float_list = basic_option_list<float>;
	using option_double_list = basic_option_list<double>;
	using option_string_list = basic_option_list<std::string>;
}