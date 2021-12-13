#pragma once

namespace stx::chrono {
	// Time incrementer
	// Returns true and reset if duration has passed
	class Wait {
	public:
		Wait(double duration) {
			this->duration = duration;
			this->time = this->duration;
		}
		// Returns true every x seconds
		bool operator()(double dt) {
			this->time -= dt;
			bool finished = time <= 0.0; 
			if(finished) {
				this->time = duration;
			}
			return finished;
		}
	private:
		double duration;
		double time;
	};
}