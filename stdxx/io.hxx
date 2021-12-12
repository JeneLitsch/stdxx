#pragma once
#include <istream>
#include <ostream>
#include <iostream>
#include <fstream>
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

	template<typename T>
	inline T read() {
		return read<T>(std::cin);
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
}
