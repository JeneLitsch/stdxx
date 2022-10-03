#pragma once
#include <optional>

namespace stx {
	struct nullref_t {} nullref;



	template<typename T>
	class optref final {
	public:

		constexpr optref()
		: t{nullptr} {}



		constexpr optref(T & t)
		: t{&t} {}
		
		
		
		constexpr optref(std::nullopt_t)
		: t{nullptr} {}



		constexpr optref(nullref_t)
		: t{nullptr} {}



		constexpr optref(std::nullptr_t)
		: t{nullptr} {}
		
		

		constexpr optref(T && t) = delete;



		constexpr operator bool() {
			return this->t;
		} 



		constexpr T & operator*() const {
        	return *this->t;
    	}



		constexpr T * operator&() const {
        	return this->t;
    	}



    	constexpr T * operator->() const {
        	return this->t;
    	}



		constexpr T & value() const {
			if(this->t) return *this->t;
			throw std::bad_optional_access {};
		}



		constexpr T & value_or(T & alt) {
			if(this->t) return *this->t;
			else return alt;
		}



		
		inline friend bool operator==(const optref & l, const optref & r) {
			return std::equal_to<void>{}(l.t, r.t);
		} 



		inline friend auto operator<=>(const optref & l, const optref & r) {
			return std::compare_three_way{}(l.t, r.t);
		} 


		
		constexpr T & value_or(T && alt) = delete;

	private:
		T * t = nullptr;
	};
}