#pragma once
#include "lerp.hxx"
#include "invlerp.hxx"
#include "ease.hxx"

namespace stx {
    template<typename In, typename Out>
    Out remap(In i_min, In i_max, Out o_min, Out o_max, In input, const auto & ease) {
        const auto t = invlerp<In>(i_min, i_max, input);
        return lerp<Out>(o_min, o_max, t, ease);
    }



	template<typename In, typename Out>
    Out remap(In i_min, In i_max, Out o_min, Out o_max, In input) {
		return remap(i_min, i_max, o_min, o_max, input, ease::clamp);
    }
}