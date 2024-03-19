#include "TurnEngine/core/Object2D.hpp"

namespace TurnEngine::core {

    Object2D::Object2D(
            geo2d::Shape<int>* shape,
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
            shape,
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
    ), Object("") {}

    Object2D::Object2D(Object2D *drawable) : IObject2D(
            drawable->shape,
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
    ), Object(drawable) {}

    void Object2D::draw(render::Drawer *drawer) {
        drawer->draw(*this);
    }

    Object2D* Object2D::getChild(std::string _name) {
        if (_name == getName()) return this;
        return nullptr;
    }

}