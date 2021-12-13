#pragma once
#include <chrono>

namespace stx::chrono {
	// Returns seconds as double between two calls
	template<std::floating_point T>
	class Clock {
	public:
		Clock() {
			this->prev = this->clock.now();
		}

		T operator()() {
			auto now = this->clock.now();
			auto dt = std::chrono::duration<T>(now - this->prev);  
			this->prev = now;
			return dt.count();
		}
	private:
		std::chrono::steady_clock clock;
		std::chrono::time_point<std::chrono::steady_clock> prev;
	};

	using Clockf = Clock<float>;
	using Clockd = Clock<double>;
}