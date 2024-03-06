#pragma once

#include "TurnEngine/core/IDrawable.hpp"
#include "TurnEngine/render/Drawer.hpp"

namespace TurnEngine::core {
    class Drawable : public IDrawable {
    public:
        Drawable(int depthIndex, bool isAnimated, Point<int> position, int width, int height, Texture *texture,
                 Rect<int> rect, int angle = 0, RendererFlip flip = RendererFlip::NONE, rgba<> color = Color::black);
        Drawable(Drawable* drawable);
        void draw(render::Drawer* drawer);
    };
}