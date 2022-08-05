#pragma once
#include <vector>

namespace stx {
	template<typename T, typename Container = std::vector<T>>
	class accu_stack {
	public:
		accu_stack(T base = T{}) : base { base } {}

		const T & top() const {
			return this->empty() ? base : data.back();
		}

		void pop() {
			data.pop_back();
		}

		void push(const T & inner) {
			data.push_back(this->top() + inner);
		}

		bool empty() const {
			return data.empty();
		}

	private:
		T base; 
		Container data;
	};
}