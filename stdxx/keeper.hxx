#pragma once
#include "oop.hxx"

namespace stx {
	template<typename T>
	class keeper : non_copyable, non_moveable {
	public:
		keeper(T & t)
			: ptr{&t}
			, value{t} {}
		
		~keeper() {
			(*ptr) = value;
		}

	private:
		T * ptr;
		T value;
	};
}