#pragma once

#include "TurnEngine/core/IObject2D.hpp"

namespace TurnEngine::render {
    /// @brief
    /// Class represents Object2D comparator.
    /// It compares 2D objects by its depthIndex
    class DrawComparator {
    public:
        bool operator()(const core::IObject2D& below, const core::IObject2D& above) const;
    };
}