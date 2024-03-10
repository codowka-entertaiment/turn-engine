#pragma once

#include "TurnEngine/core/Object2D.hpp"
#include "TurnEngine/core/Subject.hpp"
#include "TurnEngine/geo2d/shapes/Shape.hpp"
#include "TurnEngine/gui/Label.hpp"

namespace TurnEngine::gui {
    class BaseButton : public core::Object2D {
    private:
        Texture *commonTexture;
        Texture *onHover;
        std::function<void()> handler;
        std::string text;
        Label* label;
        void emptyFunc() {};
    public:
        BaseButton(geo2d::Shape<int> *_shape,
                   int _depthIndex,
                   Point<int> _position,
                   int _width,
                   int _height,
                   Texture *_commonTexture,
                   Texture *_onHoverTexture,
                   int _angle,
                   RendererFlip _flip,
                   rgba<> color,
                   std::string _text,
                   std::string _font,
                   int _fontSize);

        void update(core::Event* _event) override;

        void draw(render::Drawer* drawer) override;

        void setHandler(std::function<void(void)> _func);

    };
}