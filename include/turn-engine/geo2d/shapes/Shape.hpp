#pragma once

#include "../Vector.hpp"

#include <cinttypes>
#include <expected>

namespace geo2d
{
    template <Numeric T>
    struct Shape {
        constexpr virtual bool contains(const Position<T> &position) const noexcept = 0;
    };
}