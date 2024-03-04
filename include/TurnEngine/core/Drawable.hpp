#pragma once

#include "TurnEngine/wrapper/Shapes.hpp"
#include "TurnEngine/wrapper/Texture.hpp"
#include "TurnEngine/wrapper/Utils.hpp"
#include "TurnEngine/wrapper/Color.hpp"

namespace TurnEngine::core {
    struct Drawable {
        int depthIndex;
        bool isAnimated;
        Point<int> position;
        int width;
        int height;
        Texture* texture;
        Rect<int> rect;
        int angle = 0;
        RendererFlip flip = RendererFlip::NONE;
        rgba<> color;
    };
}