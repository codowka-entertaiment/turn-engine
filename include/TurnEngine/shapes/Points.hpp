#pragma once

#include <vector>
#include "TurnEngine/core/Drawable.hpp"

namespace TurnEngine::shapes {
    class Points: core::Drawable {
    private:
        std::vector<Point<int>> points;
    public:
        std::vector<Point<int>> getPoints();
    };
}