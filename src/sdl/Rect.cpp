#include "turn-engine/sdl/Rect.hpp"

sdl::Rect::Rect(geo2d::PositionInt vertex, int width, int height) : geo2d::RectangleInt(vertex, width, height) {}

sdl::Rect::operator SDL_Rect() const {
    return SDL_Rect(this->m_vertex.x, this->m_vertex.y, this->width(), this->height());
}