#pragma once
#include <ostream>
#include <istream>
#include "../iife.hxx"
namespace stx {

	template<typename String>
	class escaped {
	public:
		escaped(String & str) : str(str) {}
		


		void operator()(std::istream & in) const {
			str.clear();
			if(in.get() != '"') return in.setstate(std::ios_base::failbit);
			while(true) {
				int c = in.get();
				static constexpr auto eof = std::char_traits<char>::eof();
				if(c == eof) return in.setstate(std::ios_base::failbit);
				if(c == '"') return;
				if(c == '\\') {
					switch (in.get()) {
					case 'n':  c = '\n'; break;
					case '"':  c = '\"'; break;
					case 't':  c = '\t'; break;
					case 'r':  c = '\r'; break;
					case '\\': c = '\\'; break;
					
					default: return in.setstate(std::ios_base::failbit);
					}
				}
				str.push_back(static_cast<char>(c));
			}
		}



		void operator()(std::ostream & out) const {
			out << '"';
			for(const char c : str) {
				switch (c) {
				case '\n': out << "\\n"; break;
				case '\t': out << "\\t"; break;
				case '\r': out << "\\r"; break;
				case '\"': out << "\\\""; break;
				case '\\': out << "\\\\"; break;				
				default: out << c;
				}
			}
			out << '"';
		}

		

	private:
		String & str;
	};


	template<typename String>
	inline std::istream & operator>>(std::istream & in, const escaped<String> & e) {
		e(in);
		return in;
	}

	template<typename String>
	inline std::ostream & operator<<(std::ostream & out, const escaped<String> & e) {
		e(out);
		return out;
	}
}