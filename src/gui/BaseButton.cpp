#include "TurnEngine/gui/BaseButton.hpp"

namespace TurnEngine::gui {

    BaseButton::BaseButton(
            geo2d::Shape<int>* _shape,
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
            int _fontSize
    ): core::Object2D(_shape, _depthIndex, false, _position, _width, _height, _commonTexture, {0, 0, 0, 0}, _angle, _flip) {
        text = _text;
        handler = [](){};
        label = new gui::Label(
                new Font(_font, _fontSize),
                text,
                {_position.x() + _width / 2, _position.y() + _height / 2},
                {0xff, 0xff, 0xff, 0xff},
                _depthIndex + 1
        );
    }

    void BaseButton::update(core::Event* _event) {
        if (shape->contains({_event->pos.x(), _event->pos.y()}) && _event->msg == "click") {
            handler();
        }
    }

    void BaseButton::draw(render::Drawer* drawer) {
        label->draw(drawer);
        label->position = {
                position.x() + width / 2 - label->width / 2,
                position.y() + height / 2 - label->height / 2
        };
        drawer->draw(*this);
        label->draw(drawer);
    }

    void BaseButton::setHandler(std::function<void(void)> _func) {
        handler = _func;
    }

}