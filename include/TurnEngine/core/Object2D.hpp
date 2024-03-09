#pragma once

#include "TurnEngine/core/IObject2D.hpp"
#include "TurnEngine/render/Drawer.hpp"

namespace TurnEngine::core {
    class Object2D : public IObject2D {
    public:
        Object2D(int depthIndex, bool isAnimated, Point<int> position, int width, int height, Texture *texture,
                 Rect<int> rect, int angle = 0, RendererFlip flip = RendererFlip::NONE, rgba<> color = Color::black);
        Object2D(Object2D* drawable);
        void draw(render::Drawer* drawer);
    };
}