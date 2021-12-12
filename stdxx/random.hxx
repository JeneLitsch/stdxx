#pragma once
#include <random>
#include <concepts>

namespace cxx {
	template<typename Numeric>
	Numeric rand(auto & rng, Numeric from, Numeric to) {
		if constexpr (std::is_floating_point<Numeric>::value) {
			std::uniform_real_distribution<Numeric> dist{from, to};
			return dist(rng);
		}
		else {
			std::uniform_int_distribution<Numeric> dist{from, to};
			return dist(rng);
		}
	}

	void seed(auto & rng) {
		std::random_device rngDevice;
		rng.seed(rngDevice());
	}
}