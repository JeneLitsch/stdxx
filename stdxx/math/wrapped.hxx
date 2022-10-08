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
		: val{val}, min{min}, max{max} {
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

	private:
		constexpr T wrap(T t) const {
			const T range = max - min + 1;
			if(t < this->min) t += range * ((min - t) / range + 1);
			return min + mod(t - min, range); 
		}
		T val;
		T min;
		T max;
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