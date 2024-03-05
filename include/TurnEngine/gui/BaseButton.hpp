#pragma once

#include "TurnEngine/core/Drawable.hpp"
#include "TurnEngine/core/Subject.hpp"

namespace TurnEngine::gui {
    class BaseButton: core::Drawable {
    private:
        std::string text;
    };
}