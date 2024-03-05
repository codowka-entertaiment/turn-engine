#pragma once

#include "TurnEngine/core/IDrawable.hpp"

namespace TurnEngine::render {
    class DrawComparator {
    public:
        bool operator()(const core::IDrawable& below, const core::IDrawable& above) const;
    };
}