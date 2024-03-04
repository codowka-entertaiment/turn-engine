#pragma once

#include "TurnEngine/core/Drawable.hpp"

namespace TurnEngine::render {
    class DrawComparator {
    public:
        bool operator()(const core::Drawable& below, const core::Drawable& above) const;
    };
}