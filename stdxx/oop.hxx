#pragma once
namespace stx {
	struct non_copyable {
		non_copyable(const non_copyable &) = delete;
		non_copyable & operator=(const non_copyable &) = delete;
		non_copyable() = default;
	};

	struct non_moveable {
		non_moveable(non_moveable &&) = delete;
		non_moveable & operator=(non_moveable &&) = delete;
		non_moveable() = default;
	};
}