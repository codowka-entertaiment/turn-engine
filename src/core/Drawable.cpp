#include "TurnEngine/core/Object2D.hpp"

namespace TurnEngine::core {

    Object2D::Object2D(
            int depthIndex,
            bool isAnimated,
            Point<int> position,
            int width,
            int height,
            Texture *texture,
            Rect<int> rect,
            int angle,
            RendererFlip flip,
            rgba<> color
    ) : IObject2D(
            depthIndex,
            isAnimated,
            position,
            width,
            height,
            texture,
            rect,
            angle,
            flip,
            color
    ) {}

    Object2D::Object2D(Object2D *drawable) : IObject2D(
            drawable->depthIndex,
            drawable->isAnimated,
            drawable->position,
            drawable->width,
            drawable->height,
            drawable->texture,
            drawable->rect,
            drawable->angle,
            drawable->flip,
            drawable->color
    ) {}

    void Object2D::draw(render::Drawer *drawer) {
        drawer->draw(*this);
    }

}