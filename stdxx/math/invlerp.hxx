#pragma once
#include <concepts>

namespace stx {
    namespace internal {
        auto invlerp_impl(
            std::floating_point auto a,
            std::floating_point auto b,
            std::floating_point auto x) {
            
            return (x - a) / (b - a);
        }



        auto invlerp_impl(
            std::signed_integral auto a,
            std::signed_integral auto b,
            std::signed_integral auto x) {
            
            return static_cast<double>(x - a) / static_cast<double>(b - a);
        }



        auto invlerp_impl(
            std::unsigned_integral auto a,
            std::unsigned_integral auto b,
            std::unsigned_integral auto x) {
            
			const auto l = std::min(a, b);
			const auto h = std::max(a, b);
            const auto t = static_cast<double>(x - l) / static_cast<double>(h - l);

            return a < b ? t : 1 - t;
        }
    }
    


    template<typename T>
    double invlerp(const T & a, const T & b, const T & x) {
        return static_cast<double>(internal::invlerp_impl(a,b,x));
    }
}