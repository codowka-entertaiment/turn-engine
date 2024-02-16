#pragma once

#include <functional>
#include <limits>

namespace math
{
#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
    double constexpr sqrt(double x) {
        constexpr auto sqrt_newton_raphson = [](double x, double c, double p) noexcept -> double {
            auto sqrt_newton_raphson_impl = [](double x, double c, double p, auto &ref) noexcept -> double {
                return c == p ? c : ref(x, 0.5 * (c + x / c), c, ref);
            };
            return sqrt_newton_raphson_impl(x, c, p, sqrt_newton_raphson_impl);
        };

        return x >= 0 && x < std::numeric_limits<double>::infinity() ? sqrt_newton_raphson(x, x, 0)
                                                                     : std::numeric_limits<double>::quiet_NaN();
    }
#pragma clang diagnostic pop
}