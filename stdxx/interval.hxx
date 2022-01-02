#pragma once
#include "concepts.hxx"
namespace stx {
	template<class T> requires std::integral<T>
	class interval {
	public:
		class iterator {
		public:
			iterator(T value) : value(value) {}

			using iterator_category = std::input_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = T;
			using pointer = T*;
			using reference = T&;

			const value_type & operator*() const {
				return this->value;
			}

			const value_type * operator->() const {
				return &this->value;
			}

			iterator operator++() {
				this->value++; return *this;
			}

			iterator operator++(int) {
				iterator temp = *this;
				this->value++;
				return temp;
			}

			friend bool operator==(const iterator & l, const iterator & r) {
				return l.value == r.value;
			}

			friend bool operator!=(const iterator & l, const iterator & r) {
				return l.value != r.value;
			}

		private:
			value_type value;
		};

		iterator begin() const {
			return iterator{first};
		}

		iterator end() const {
			return iterator{last};
		}

		interval(T first, T last) : first(first), last(last) {}
		interval(T last) : first(0), last(last) {}


		T size() const { 
			return last - first;
		}
	private:
		T first;
		T last;
	};

	template<typename T>
	auto size(const interval<T> & i) {
		return i.size();
	}

	using interval_i = interval<int>;
	using interval_u = interval<unsigned>;
	using interval_s = interval<std::size_t>;

	template<typename T>
	auto over(const auto & container) {
		return interval<T>(static_cast<T>(container.size()));
	}

	auto over_i(const auto & container) { return over<int>(container); }
	auto over_u(const auto & container) { return over<unsigned>(container); }
	auto over_s(const auto & container) { return over<std::size_t>(container); }
}