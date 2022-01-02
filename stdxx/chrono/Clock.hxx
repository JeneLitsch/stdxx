#pragma once
#include <chrono>

namespace stx::chrono {
	// Returns seconds as double between two calls
	template<std::floating_point T>
	class clock {
	public:
		clock() {
			this->prev = this->stdclock.now();
		}

		T operator()() {
			auto now = this->stdclock.now();
			auto dt = std::chrono::duration<T>(now - this->prev);  
			this->prev = now;
			return dt.count();
		}
	private:
		std::chrono::steady_clock stdclock;
		std::chrono::time_point<std::chrono::steady_clock> prev;
	};

	using clock_f = clock<float>;
	using clock_d = clock<double>;
}