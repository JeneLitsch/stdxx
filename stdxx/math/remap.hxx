#pragma once
#include "lerp.hxx"
#include "invlerp.hxx"

namespace stx {
    template<typename In, typename Out>
    Out remap(In i_min, In i_max, Out o_min, Out o_max, In input) {
        const auto t = invlerp<In>(i_min, i_max, input);
        return lerp(o_min, o_max, std::clamp<double>(t, 0, 1));
    }
}