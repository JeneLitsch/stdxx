#include <vector>
#include <sstream>
#include <ostream>
#include <iterator>
#include "memory.hxx"
#include "algorithm.hxx"
#include "iterator.hxx"
#include "io.hxx"


namespace stx {

	namespace internal {
		inline void read_from_stream(bool & value, std::istream & in) {
			const bool ba = std::isalpha((in >> std::ws).peek());
			in >> (ba ? std::boolalpha : std::noboolalpha) >> value;
		}

		inline void read_from_stream(auto & value, std::istream & in) {
			in >> value;
		}
	}


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



	template<typename T>
	class option_value final : public option {
	public:
		option_value(const std::vector<std::string> & names,
			const std::string & title,
			const std::string & descr,
			T default_value = T{}) :
			option { names, title, descr },
			value { default_value } {}

		option_value(const std::string & name,
			const std::string & title,
			const std::string & descr,
			T default_value = T{}) :
			option_value { std::vector{name}, title, descr, default_value } {}

		option_value(const option_value &) = default; 
		option_value(option_value &&) = default; 
		option_value & operator=(const option_value &) = default; 
		option_value & operator=(option_value &&) = default; 
		
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
	private:
		T value = T{};
		bool set = false;
	};


	template<typename T>
	class option_list final : public option {
	public:
		option_list(
			const std::vector<std::string> & names,
			const std::string & title,
			const std::string & descr) : 
			option { names, title, descr } {}

		option_list(
			const std::string & name,
			const std::string & title,
			const std::string & descr) : 
			option_list { std::vector{name}, title, descr } {}

		option_list(const option_list &) = default; 
		option_list(option_list &&) = default; 
		option_list & operator=(const option_list &) = default; 
		option_list & operator=(option_list &&) = default; 
		
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
	private:
		bool set = false;
		std::vector<T> array;
	};



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


		void parse(std::istream & in) {
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

			std::string arg = fetch_first(in);
			while(!arg.empty()) {
				bool invalid_option = none_of_short_ciruit(begin, end, [&] (auto & option) {
					return option->parse(arg, in); 
				});

				if(invalid_option) throw std::runtime_error {
					"Unkown option " + arg
				};

				arg = fetch(in);
			};
		} 
	private:
		std::vector<std::unique_ptr<option>> options;
		std::string program_name;
		std::string overview;
	};



	class args {
	public:
		args(int argc, char const *argv[]) :
			argc { argc },
			argv { argv } {}

		std::string_view command() const {
			if(argc == 0) return "";
			return argv[0];
		}

		std::string str() const {
			std::ostringstream oss;
			separate_by(argv, argv + argc, oss, " ");
			return oss.str();
		}

		void parse_options(option_description & desc) {
			std::istringstream iss { this->str() };
			desc.parse(iss);
		}

		auto begin() { return argv; }
		auto begin() const { return argv; }
		auto cbegin() const { return argv; }

		auto end() { return argv + argc; }
		auto end() const { return argv + argc; }
		auto cend() const { return argv + argc; }

	private:
		int argc;
		char const ** argv;
	};
}