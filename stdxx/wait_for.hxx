#pragma once
#include <future>
namespace stx {
	template<class T>
	class wait_for {
	public:
		wait_for() = default;
		wait_for(const wait_for &) = delete;
		wait_for(wait_for &&) = delete;
		wait_for & operator=(const wait_for &) = delete;
		wait_for & operator=(wait_for &&) = delete;

		void operator()(const T & t) {
			return this->set(t);
		}
		
		void set(const T & t) {
			promise.set_value(t);
		}
		
		T wait() {
			return promise.get_future().get();
		}
	private:
		std::promise<T> promise;
	};


	template<>
	class wait_for<void> {
	public:
		wait_for(const wait_for &) = delete;
		wait_for(wait_for &&) = delete;
		wait_for & operator=(const wait_for &) = delete;
		wait_for & operator=(wait_for &&) = delete;

		wait_for() {
			mutex.lock();
		}

		void operator()() {
			return this->set();
		}

		void set() {
			mutex.unlock();
		}

		void wait() {
			std::lock_guard{mutex};
			return;
		}

	private:
		std::mutex mutex;
	};

	template<class T>
	auto wait(wait_for<T> & wf) {
		return wf.wait();
	}
}