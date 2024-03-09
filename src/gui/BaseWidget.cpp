#include "TurnEngine/gui/BaseWidget.hpp"

namespace TurnEngine::gui {
    BaseWidget::BaseWidget(int _depthIndex,
                           Point<int> _position,
                           int _width,
                           int _height,
                           Texture *_texture,
                           geo2d::Shape<int> *_shape,
                           int _angle = 0,
                           RendererFlip _flip = RendererFlip::NONE,
                           rgba<> color = Color::black
    ) : core::Object2D({_depthIndex, false, _position, _width, _height, _texture, {0, 0, 0, 0}, _angle, _flip, color}) {
        shape = _shape;
    }

    BaseWidget::~BaseWidget() = default;

    void BaseWidget::addChild(core::Object2D *child) {
        children.push_back(child);
    }

    BaseWidget::BaseWidget(core::Object2D *drawable, geo2d::Shape<int> *_shape) :
            core::Object2D(*drawable), shape(_shape) {}

    BaseWidget::BaseWidget(BaseWidget *widget) : core::Object2D(
            widget->depthIndex,
            false,
            widget->position,
            widget->width,
            widget->height,
            widget->texture,
            {0, 0, 0, 0},
            widget->angle,
            widget->flip,
            widget->color
    ) {
        shape = widget->shape;
    }
}