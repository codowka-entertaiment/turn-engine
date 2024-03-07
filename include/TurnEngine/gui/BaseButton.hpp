#pragma once

#include "TurnEngine/core/Drawable.hpp"
#include "TurnEngine/core/Subject.hpp"
#include "TurnEngine/geo2d/shapes/Shape.hpp"

namespace TurnEngine::gui {
    class BaseButton : public core::Drawable, public core::Subject {
    private:
//        std::string text;
        geo2d::Shape<int> *shape;
        Texture* commonTexture;
        Texture* onHover;
    public:
        BaseButton(int _depthIndex,
                   Point<int> _position,
                   int _width,
                   int _height,
                   Texture *_texture,
                   geo2d::Shape<int> *_shape,
                   int _angle,
                   RendererFlip _flip,
                   rgba<> color,
                   std::string _text);

        BaseButton(core::Drawable *drawable, geo2d::Shape<int> *_shape, std::string _text);



    };
}