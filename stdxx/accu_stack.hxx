#pragma once
#include <deque>

namespace stx {
	template<typename T, typename Container = std::deque<T>>
	class accu_stack {
	public:

		accu_stack(T init = T{}) : init { init } {}



		const T & top() const {
			return this->empty() ? init : data.back();
		}



		void pop() {
			data.pop_back();
		}



		void push(const T & t) {
			data.push_back(this->top() + t);
		}



		void push(T && t) {
			data.push_back(this->top() + t);
		}



		bool empty() const {
			return data.empty();
		}



		typename Container::size_type size() const {
			return data.size();
		}



		template<typename ... Args>
		auto emplace(Args &&... args) {
			return data.emplace_back(this->top() + T{std::forward<Args>(args)...});
		}


		void swap(accu_stack & other) noexcept {
			std::swap(this->init, other.init);
			std::swap(this->data, other.data);
		}


	private:
		T init; 
		Container data;
	};
}