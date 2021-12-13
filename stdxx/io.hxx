#pragma once
#include <istream>
#include <ostream>
#include <iostream>
#include <fstream>
#include <tuple>
#include "concepts.hxx"

namespace stx {
	inline void print(std::ostream & stream, auto data) {
		stream << data;
	}

	inline void print(auto data) {
		print(std::cout, data);
	}

	inline void println(std::ostream & stream, auto data) {
		stream << data << "\n";
	}

	inline void println(auto data) {
		println(std::cout, data);
	}



	
	template<typename T>
	inline T read(std::istream & in) {
		T value;
		in >> value;
		return value;
	}
	
	template<vector_2 T>
	inline T read(std::istream & in) {
		const auto x = read<decltype(T::x)>(in);
		const auto y = read<decltype(T::y)>(in);
		return T{x, y};
	}

	template<vector_3 T>
	inline T read(std::istream & in) {
		const auto x = read<decltype(T::x)>(in);
		const auto y = read<decltype(T::y)>(in);
		const auto z = read<decltype(T::z)>(in);
		return T{x, y, z};
	}

	template<typename...T>
	inline auto read() {
		return read<T...>(std::cin);
	}

	
	inline std::string readln(std::istream & stream) {
		std::string str;
		std::getline(stream, str);
		return str;
	}
	
	inline std::string readln() {
		return readln(std::cin);
	}

	inline bool isEof(std::istream & stream) {
		return stream.eof();
	}

	inline bool isEof() {
		return isEof(std::cin);
	}

	template<typename T>
	inline std::tuple<T> read_n(std::istream & in) {
		return std::make_tuple(read<T>(in));
	}

	template<typename T1, typename T2, typename... Ts>
	inline auto read(std::istream & in) {
		auto tuple1 = std::tuple{read<T1>(in)};
		auto tuple2 = std::tuple{read<T2, Ts...>(in)};
		return std::tuple_cat(tuple1, tuple2);
	}

}

std::ostream & operator<<(std::ostream & stream, const stx::color_rgb auto & color) {
	return stream << "rgb(" 
		<< static_cast<unsigned>(color.r) << ","
		<< static_cast<unsigned>(color.g) << ","
		<< static_cast<unsigned>(color.b) << ")";
}

std::ostream & operator<<(std::ostream & stream, const stx::color_rgba auto & color) {
	return stream << "rgba(" 
		<< static_cast<unsigned>(color.r) << ","
		<< static_cast<unsigned>(color.g) << ","
		<< static_cast<unsigned>(color.b) << ","
		<< static_cast<unsigned>(color.a) << ")";
}