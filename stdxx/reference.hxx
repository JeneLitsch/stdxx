#pragma once
#include <memory>

namespace stx {
	// Alternative to std::reference_wrapper
	// For personal taste reasons
	template<class T>
	class reference {
	public:
		constexpr reference(T & ref) : ptr(&ref) {}
		constexpr reference & operator=(T & ref) {
			this->ptr = ref;
			return *this;
		}


		constexpr operator T&() {
			return **this;
		}
		constexpr operator const T &() const {
			return **this;
		}


		constexpr T * operator->() {
			return this->ptr;
		}
		constexpr const T * operator->() const {
			return this->ptr;
		}


		constexpr T & operator*() {
			return *this->ptr;
		}
		constexpr const T & operator*() const {
			return *this->ptr;
		}

	private:
		T * ptr;
	};

	template<typename T>
	reference<T> ref(T & ref) {
		return reference<T>(ref);
	}

	template<typename T>
	reference<const T> cref(const T & ref) {
		return reference<const T>(ref);
	}

	template<typename T>
	reference<T> ref(std::unique_ptr<T> & ref) {
		return reference<T>(*ref);
	}

	template<typename T>
	reference<const T> cref(std::unique_ptr<const T> & ref) {
		return reference<const T>(*ref);
	}

	auto ref(auto begin, auto end, auto insert) {
		while (begin != end) {
        	*insert++ = ref(*begin++);
    	}
    	return insert;
	}

	auto cref(auto begin, auto end, auto insert) {
		while (begin != end) {
        	*insert++ = cref(*begin++);
    	}
    	return insert;
	}
}