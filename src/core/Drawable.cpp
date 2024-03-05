#include "TurnEngine/core/Drawable.hpp"

namespace TurnEngine::core {

    Drawable::Drawable(int depthIndex, bool isAnimated, Point<int> position, int width, int height, Texture *texture,
                       Rect<int> rect, int angle, RendererFlip flip, rgba<> color)
                       : IDrawable(depthIndex, isAnimated, position, width, height, texture, rect, angle, flip, color)
                       {}
    void Drawable::draw(render::Drawer* drawer) {
        drawer->draw(*this);
    }
}