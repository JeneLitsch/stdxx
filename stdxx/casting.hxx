#pragma once

namespace cxx {
	template<class To, class From>
	To * as(From & from) {
		return dynamic_cast<To*>(&from);
	}
}
