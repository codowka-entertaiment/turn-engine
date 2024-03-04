#pragma once

#include "TurnEngine/core/Drawable.hpp"
#include "TurnEngine/core/Subject.hpp"

namespace TurnEngine::gui {
    class Button: core::Drawable, core::Subject {
    private:
        std::string text;

    };
}