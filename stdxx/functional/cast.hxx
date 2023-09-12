#pragma once

namespace stx::fx {
	template<typename Out>
	struct static_cast_to {
		Out operator() (const auto & x) const {
			return static_cast<Out>(x);
		}
	};
}