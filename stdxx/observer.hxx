#pragma once
#include <vector>
#include <functional>
#include <memory>
#include "reference.hxx"

namespace stx {
	template<typename ... Data>
	class observable {
	public:
		using observer = std::function<void(const Data &...)>; 
		stx::reference<observer> add_observer(observer observer) {
			this->observers.push_back(std::make_unique<observable::observer>(std::move(observer)));
			return *this->observers.back();
		}



		void remove_observer(stx::reference<observer> observer) {
			std::erase_if(this->observers, [&] (const auto & o) {
				return observer == stx::reference{*o};
			});
		}



		void notify(const Data & ... data) {
			for(const auto & o : this->observers) {
				(*o)(data...);
			}
		}
	private:
		std::vector<std::unique_ptr<observer>> observers;
	};
}