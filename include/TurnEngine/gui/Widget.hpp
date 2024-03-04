#pragma once

#include <vector>

#include "TurnEngine/core/Object2D.hpp"
#include "TurnEngine/core/Drawable.hpp"
#include "TurnEngine/core/Responsible.hpp"
#include "TurnEngine/render/Drawer.hpp"

namespace TurnEngine::gui {

    /// @brief
    /// Widget(int _depthIndex, Point<int> _position, int _width, int _height, Texture *_texture, int _angle, RendererFlip _flip)
    class Widget : public core::Drawable {
    private:
        std::vector<core::Drawable *> children;
    public:
        Widget(int _depthIndex,
               Point<int> _position,
               int _width,
               int _height,
               Texture *_texture,
               int _angle,
               RendererFlip _flip,
               rgba<> color);

        Widget(core::Drawable* drawable);

        ~Widget();

        void addChild(core::Drawable *child);
    };
}