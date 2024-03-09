#include "TurnEngine/gui/BaseButton.hpp"

namespace TurnEngine::gui {

    BaseButton::BaseButton(
            int _depthIndex,
            Point<int> _position,
            int _width,
            int _height,
            Texture *_commonTexture,
            Texture *_onHoverTexture,
            geo2d::Shape<int> *_shape,
            int _angle,
            RendererFlip _flip,
            rgba<> color, std::string _text
    ): core::Object2D({_depthIndex, false, _position, _width, _height, nullptr, {0, 0, 0, 0}, _angle, _flip}) {

    }
}