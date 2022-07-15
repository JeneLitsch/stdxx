#pragma once
#include "stdxx/args/option.hxx"
#include "stdxx/args/read_from_stream.hxx"
	
namespace stx {
	template<typename T>
	class basic_option_value final : public option {
	public:
		basic_option_value(const std::vector<std::string> & names,
			const std::string & title,
			const std::string & descr,
			T default_value = T{}) :
			option { names, title, descr },
			value { default_value } {}

		basic_option_value(const std::string & name,
			const std::string & title,
			const std::string & descr,
			T default_value = T{}) :
			basic_option_value { std::vector{name}, title, descr, default_value } {}

		basic_option_value(const basic_option_value &) = default; 
		basic_option_value(basic_option_value &&) = default; 
		basic_option_value & operator=(const basic_option_value &) = default; 
		basic_option_value & operator=(basic_option_value &&) = default; 
		
		virtual bool parse(const std::string_view & name, std::istream & in) override {			
			if(!this->matches(name)) return false;
			this->set = true;
			internal::read_from_stream(this->value, in);

			if(!in) throw std::runtime_error {
				"Invalid option value"
			};

			return true;
		}

		virtual void mandatory() const override {
			if(!this->set) throw std::runtime_error {
				this->get_main_name() + " is a mandatory option."
			};
		}

		const T & get() const {
			return this->value;
		}

		bool is_set() const {
			return this->set;
		}
	private:
		T value = T{};
		bool set = false;
	};

	using option_bool = basic_option_value<bool>;
	using option_int = basic_option_value<int>;
	using option_long = basic_option_value<long>;
	using option_float = basic_option_value<float>;
	using option_double = basic_option_value<double>;
	using option_string = basic_option_value<std::string>;
}