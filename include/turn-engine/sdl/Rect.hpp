#pragma once

#include <SDL.h>

#include "turn-engine/geo2d/Shapes.hpp"
#include "turn-engine/geo2d/Vector.hpp"

namespace sdl
{
    class Rect : public geo2d::RectangleInt {
    public:
        Rect(geo2d::PositionInt vertex, int width, int height);
        operator SDL_Rect() const;
    };
}