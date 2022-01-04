#pragma once
#include "concepts.hxx"
namespace stx {
	template<class T> requires std::integral<T>
	class interval {
	public:
		class iterator {
		public:
			constexpr iterator(T value) : value(value) {}

			using iterator_category = std::input_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = T;
			using pointer = T*;
			using reference = T&;

			constexpr const value_type & operator*() const {
				return this->value;
			}

			constexpr const value_type * operator->() const {
				return &this->value;
			}

			constexpr iterator operator++() {
				this->value++; return *this;
			}

			constexpr iterator operator++(int) {
				iterator temp = *this;
				this->value++;
				return temp;
			}

			constexpr friend bool operator==(const iterator & l, const iterator & r) {
				return l.value == r.value;
			}

			constexpr friend bool operator!=(const iterator & l, const iterator & r) {
				return l.value != r.value;
			}

		private:
			value_type value;
		};

		constexpr iterator begin() const {
			return iterator{first};
		}

		constexpr iterator end() const {
			return iterator{last};
		}

		constexpr interval(T first, T last) : first(first), last(last) {}
		constexpr interval(T last) : first(0), last(last) {}


		constexpr T size() const { 
			return last - first;
		}
	private:
		T first;
		T last;
	};

	template<typename T>
	constexpr auto size(const interval<T> & i) {
		return i.size();
	}

	using interval_i = interval<int>;
	using interval_u = interval<unsigned>;
	using interval_s = interval<std::size_t>;

	template<typename T>
	constexpr auto over(const auto & container) {
		return interval<T>(static_cast<T>(container.size()));
	}

	constexpr auto over_i(const auto & container) {
		return over<int>(container);
	}
	
	constexpr auto over_u(const auto & container) {
		return over<unsigned>(container);
	}
	
	constexpr auto over_s(const auto & container) {
		return over<std::size_t>(container);
	}
}