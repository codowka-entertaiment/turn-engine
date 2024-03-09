#pragma once

#include "TurnEngine/core/IObject2D.hpp"

namespace TurnEngine::render {
    class DrawComparator {
    public:
        bool operator()(const core::IObject2D& below, const core::IObject2D& above) const;
    };
}