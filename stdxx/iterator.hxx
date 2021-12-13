#pragma once

namespace stx {
	auto prev(auto it) {
		return --it;
	}

	auto next(auto it) {
		return --it;
	}

	auto size(const auto begin, const auto end) {
		return std::distance(begin, end);
	}

	bool empty(const auto begin, const auto end) {
		return stx::size(begin, end) == 0;
	}
}