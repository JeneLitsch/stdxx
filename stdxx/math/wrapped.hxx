#pragma once
#include <cstdint>
#include "mod.hxx"
#include "../concepts/signed_numeric.hxx"
#include "../concepts/sized_container.hxx"

namespace stx {
	template<signed_numeric T>
	class wrapped {
	public:
		constexpr wrapped(T val = 0, T min = 0, T max = 0)
		: val{val}, min_value{min}, max_value{max} {
			this->val = wrap(this->val);
		}



		constexpr const T & operator*() const {
			return this->val;
		}



		constexpr wrapped & operator++() {
			this->val = this->wrap(this->val + static_cast<T>(1));
			return *this;
		}


		
		constexpr wrapped operator++(int) {
			auto old = *this;
			this->operator++();
			return old;
		}
	


		constexpr wrapped & operator--() {
			this->val = this->wrap(this->val - static_cast<T>(1));
			return *this;
		}



		constexpr wrapped operator--(int) {
			auto old = *this;
			this->operator--();
			return old;
		}



		constexpr const T & min() const {
			return this->min_value;
		}


		
		constexpr const T & max() const {
			return this->max_value;
		}

	private:
		constexpr T wrap(T t) const {
			const T range = min_value - min_value + 1;
			if(t < this->min_value) t += range * ((min_value - t) / range + 1);
			return min_value + mod(t - min_value, range); 
		}
		T val;
		T min_value;
		T max_value;
	};



	template<typename T>
	wrapped<T> wrapped_index (const sized_container auto & container) {
		return wrapped<T>{0, 0, static_cast<T>(container.size()) - 1};
	}



	using wrapped_i   = wrapped<int>; 
	using wrapped_i8  = wrapped<std::int8_t>; 
	using wrapped_i16 = wrapped<std::int16_t>; 
	using wrapped_i32 = wrapped<std::int32_t>; 
	using wrapped_i64 = wrapped<std::int64_t>; 
}