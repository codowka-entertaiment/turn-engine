#include "TurnEngine/gui/BaseWidget.hpp"

namespace TurnEngine::gui {
    BaseWidget::BaseWidget(int _depthIndex,
                   Point<int> _position,
                   int _width,
                   int _height,
                   Texture *_texture,
                   geo2d::Shape<int>* _shape,
                   int _angle = 0,
                   RendererFlip _flip = RendererFlip::NONE,
                   rgba<> color = Color::black
    ) : core::Drawable({_depthIndex, false, _position, _width, _height, _texture, {0, 0, 0, 0}, _angle, _flip, color}) {
        shape = _shape;
    }

    BaseWidget::~BaseWidget() = default;

    void BaseWidget::addChild(core::Drawable *child) {
        children.push_back(child);
    }

    BaseWidget::BaseWidget(core::Drawable *drawable, geo2d::Shape<int>* _shape) :
            core::Drawable(*drawable), shape(_shape){}
}