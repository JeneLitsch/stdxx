#pragma once
#include <mutex>
#include "stdxx/functional.hxx"
#include "stdxx/oop.hxx"
#include <queue>
#include <future>

namespace stx {
	namespace internal {
		class task : non_copyable, non_moveable {
		public:
			virtual void operator()() = 0;
			virtual ~task() = default; 
		};



		template<typename Fx, typename Ret>
		class task_impl : public task {
		public:
			task_impl(Fx fx) : fx { fx } {}
			virtual void operator()() override {
				if constexpr(std::same_as<Ret, void>) {
					fx();
					this->promise.set_value();
				}
				else {
					this->promise.set_value(fx());
				}
			}


			std::future<Ret> get_future() {
				return this->promise.get_future();
			}

		private:
			Fx fx;
			std::promise<Ret> promise;
		};
	}



	class task_queue {
		template<typename Ret>
		using Fx = std::function<Ret(void)>;
	public:
		
		void execute() {
			std::lock_guard lock{this->mutex};
			while(!this->queue.empty()) {
				(*this->queue.front())();
				this->queue.pop();
			}
		}



		auto push(auto fx) {
			std::lock_guard lock{this->mutex};
			using Fx = decltype(fx);
			using Ret = decltype(fx());
			auto task = std::make_unique<internal::task_impl<Fx, Ret>>(fx);
			auto future = task->get_future();
			this->queue.push(std::move(task));
			return future;
		}


	private:
		std::mutex mutex;
		std::queue<std::unique_ptr<internal::task>> queue;
	};
}