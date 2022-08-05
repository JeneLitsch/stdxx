#pragma once
#include <vector>

namespace stx {
	template<typename T, typename Container = std::vector<T>>
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

		bool empty() const {
			return data.empty();
		}

	private:
		T init; 
		Container data;
	};
}