#pragma once

#include <SDL.h>

#include "turn-engine/geo2d/Shapes.hpp"
#include "turn-engine/geo2d/Vector.hpp"

namespace sdl
{
    class Rect : public geo2d::RectangleInt {
    public:
        Rect(geo2d::PositionInt vertex, int width, int height)
            : geo2d::RectangleInt(vertex, width, height){};
        operator SDL_Rect() const {
            return SDL_Rect(
                this->m_vertex.x,
                this->m_vertex.y,
                this->width(),
                this->height()
            );
        }
    };
}