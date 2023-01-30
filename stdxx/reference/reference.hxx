#pragma once
#include <memory>

namespace stx {
	// Alternative to std::reference_wrapper
	// For personal taste reasons
	template<class T>
	class reference {
	public:
		constexpr reference(T & ref) : ptr(&ref) {}
		constexpr reference(T && ref) = delete;
		
		template<class U>
		constexpr reference(reference<U> & ref) : ptr(&*ref) {}

		constexpr reference & operator=(T & ref) {
			this->ptr = &ref;
			return *this;
		}


		constexpr operator T &() const {
			return **this;
		}

		constexpr T * operator->() const {
			return this->ptr;
		}

		constexpr T & operator*() const {
			return *this->ptr;
		}

		friend auto operator<=>(const reference & l, const reference & r) {
			return std::compare_three_way{}(l.ptr, r.ptr);
		}


		friend auto operator==(const reference & l, const reference & r) {
			return (l <=> r) == 0;
		}

	private:
		T * ptr;
	};

	template<typename T>
	reference<T> to_ref(T & ref) {
		return reference<T>(ref);
	}

	template<typename T>
	reference<const T> to_cref(const T & ref) {
		return reference<const T>(ref);
	}

	template<typename T>
	reference<T> to_ref(std::unique_ptr<T> & ref) {
		return reference<T>(*ref);
	}

	template<typename T>
	reference<const T> to_cref(std::unique_ptr<const T> & ref) {
		return reference<const T>(*ref);
	}

	auto to_ref(auto begin, auto end, auto insert) {
		while (begin != end) {
        	*insert++ = ref(*begin++);
    	}
    	return insert;
	}

	auto to_cref(auto begin, auto end, auto insert) {
		while (begin != end) {
        	*insert++ = cref(*begin++);
    	}
    	return insert;
	}
}