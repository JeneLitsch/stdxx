#pragma once
#include "stdxx/args/option.hxx"
#include "stdxx/args/read_from_stream.hxx"
#include <optional>
	
namespace stx {
	template<typename T>
	class basic_option_value final : public option {
	public:
		basic_option_value(const std::vector<std::string> & names,
			const std::string & title,
			const std::string & descr) :
			option { names, title, descr } {}

		basic_option_value(const std::string & name,
			const std::string & title,
			const std::string & descr) :
			basic_option_value { std::vector{name}, title, descr } {}

		basic_option_value(const basic_option_value &) = default; 
		basic_option_value(basic_option_value &&) = default; 
		basic_option_value & operator=(const basic_option_value &) = default; 
		basic_option_value & operator=(basic_option_value &&) = default; 
		
		virtual bool parse(const std::string_view & name, std::istream & in) override {			
			if(!this->matches(name)) return false;
			T v;
			internal::read_from_stream(v, in);
			this->opt_v = v;

			if(!in) throw std::runtime_error {
				"Invalid option value"
			};

			return true;
		}

		virtual void mandatory() const override {
			if(!this->opt_v) throw std::runtime_error {
				this->get_main_name() + " is a mandatory option."
			};
		}

		const T value() const {
			if(this->opt_v) return *opt_v;
			throw std::runtime_error {
				this->get_main_name() + " is a mandatory option."
			};
		}

		const T value_or(const T && t) const {
			return opt_v.value_or(t);
		}

		operator bool() const {
			return this->opt_v;
		}
	private:
		std::optional<T> opt_v;
	};

	using option_bool = basic_option_value<bool>;
	using option_int = basic_option_value<int>;
	using option_long = basic_option_value<long>;
	using option_float = basic_option_value<float>;
	using option_double = basic_option_value<double>;
	using option_string = basic_option_value<std::string>;
}