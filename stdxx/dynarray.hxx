#pragma once
#include <memory>
#include <algorithm>

namespace stx {
	template<typename T>
	class dynarray {
	public:
		using iterator = T *;
		using const_iterator = const T *;



		dynarray(std::size_t size) {
			this->len = size;
			this->dat = std::unique_ptr<T[]>(new T[this->len]);
		}
		dynarray(std::size_t size, const T & value) 
			: dynarray(size) {
			std::fill_n(dat.get(), this->len, value);
		}
		

		
		dynarray(const dynarray & arr) {
			*this = arr;
		}
		dynarray& operator=(const dynarray & arr) {
			this->len = arr.len;
			this->dat = std::unique_ptr<T[]>(new T[this->len]);
			std::copy_n(arr.begin(), arr.len, this->begin());
			return *this;
		}



		dynarray(dynarray && arr) {
			*this = std::move(arr);
		}
		dynarray& operator=(dynarray && arr) {
			this->len = arr.len;
			arr.len = 0;
			this->dat = std::move(arr.dat);
			return *this;
		}
		


		virtual ~dynarray() = default;



		T & operator[] (std::size_t i) noexcept {
			return this->data()[i];
		}
		const T & operator[] (std::size_t i) const noexcept {
			return this->data()[i];
		}



		T * data() noexcept {
			return dat.get();
		}
		const T * data() const noexcept {
			return dat.get();
		}



		T & at(std::size_t i) {
			this->guard_size(i);
			return (*this) [i];
		}
		const T & at(std::size_t i) const {
			this->guard_size(i);
			return (*this) [i];
		}



		std::size_t size() const noexcept {
			return this->len;
		}
		std::size_t max_size() const noexcept { 
			return this->size();
		}
		std::size_t capcity() const noexcept {
			return this->size();
		}

		

		T & front() noexcept {
			return *this->begin();
		}
		const T & front() const noexcept {
			return *this->begin();
		}

		
		
		T & back() noexcept {
			return *std::prev(this->end());
		}
		const T & back() const noexcept {
			return *std::prev(this->end());
		}



		constexpr iterator begin() noexcept {
			return this->data();
		}
		constexpr const_iterator begin() const noexcept {
			return this->data();
		}
		constexpr const_iterator cbegin() const noexcept {
			return this->data();
		}



		constexpr iterator end() noexcept {
			return this->begin() + this->len;
		}
		constexpr const_iterator end() const noexcept {
			return this->begin() + this->len;
		}
		constexpr const_iterator cend() const noexcept {
			return this->begin() + this->len;
		}

	private:
		void guard_size(std::size_t i) const {
			if(i >= this->len) {
				throw std::out_of_range{""};
			}
		}

		std::unique_ptr<T[]> dat;
		std::size_t len;
	};
}