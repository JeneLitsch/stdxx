#pragma once
#include "stdxx/args/option.hxx"

namespace stx {
	class option_flag final : public option {
	public:
		option_flag(
			const std::vector<std::string> & names,
			const std::string & title,
			const std::string & descr) :
			option { names, title, descr },
			set { false } {}

		option_flag(
			const std::string & name,
			const std::string & title,
			const std::string & descr) :
			option { {name}, title, descr },
			set { false } {}

		option_flag(const option_flag &) = default; 
		option_flag(option_flag &&) = default; 
		option_flag & operator=(const option_flag &) = default; 
		option_flag & operator=(option_flag &&) = default; 

		virtual bool parse(const std::string_view & name, std::istream &) override {
			bool b = this->matches(name);
			this->set = this->set || this->matches(name);
			return b;
		}

		virtual void mandatory() const override {
			if(!this->set) throw std::runtime_error {
				this->get_main_name() + " is a mandatory option."
			};
		}

		bool is_set() const {
			return this->set;
		}
	private:
		bool set = false;
	};
}