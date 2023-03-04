#pragma once
#include <vector>
#include <functional>

namespace stx {
	template<typename ... Data>
	class observable {
	public:
		using observer = std::function<void(const Data &...)>; 
		void add_observer(observer observer) {
			this->observers.push_back(std::move(observer));
		}

		void notify(const Data & ... data) {
			for(const auto o : this->observers) {
				o(data...);
			}
		}
	private:
		std::vector<observer> observers;
	};
}