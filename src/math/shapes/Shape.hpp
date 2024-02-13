#pragma once

#include "../Math.hpp"
#include "../Vector.hpp"

#include <cinttypes>
#include <expected>

namespace math
{
    template <Numeric T>
    struct Shape {
        virtual bool contains(const Position<T> &position) const = 0;
    };
}