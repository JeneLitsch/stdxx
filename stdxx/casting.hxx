#pragma once

namespace stx {
	template<class To, class From>
	To * as(From & from) {
		return dynamic_cast<To*>(&from);
	}
}
