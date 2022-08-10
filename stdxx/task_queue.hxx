#pragma once
#include <mutex>
#include "stdxx/functional.hxx"
#include <queue>

namespace stx {
	class task_queue {
		using Fx = std::function<void(void)>;
	public:
		
		void execute() {
			std::lock_guard lock{this->mutex};
			while(!this->queue.empty()) {
				this->queue.front()();
				this->queue.pop();
			}
		}



		void push(Fx fx) {
			std::lock_guard lock{this->mutex};
			this->queue.push(fx);
		}

	private:
		std::mutex mutex;
		std::queue<Fx> queue;
	};
}