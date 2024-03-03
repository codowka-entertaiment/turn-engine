#pragma once

#include "../Vector.hpp"

#include <cinttypes>
#include <expected>

namespace TurnEngine::geo2d
{
    enum ShapeType {
        LINE, RECT, CIRCLE, HEXAGON, POINTS
    };

    template <Numeric T>
    struct Shape {
    private:
        ShapeType type{};
    public:
        constexpr virtual bool contains(const Position<T> &position) const noexcept = 0;
    };
}