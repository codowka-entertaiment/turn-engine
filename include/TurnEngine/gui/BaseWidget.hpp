#pragma once

#include <vector>

#include "TurnEngine/core/Drawable.hpp"
#include "TurnEngine/core/Responsible.hpp"
#include "TurnEngine/render/Drawer.hpp"
#include "TurnEngine/geo2d/shapes/Shape.hpp"

namespace TurnEngine::gui {

    /// @brief
    /// Widget class.
    /// It can be animated if bool isAnimated = true.
    /// It can be without texture, texture must be nullptr and color must be not null
    /// @param
    /// Widget(int _depthIndex, Point<int> _position, int _width, int _height, Texture *_texture, int _angle, RendererFlip _flip)
    class BaseWidget : public core::Drawable {
    private:
        std::vector<core::Drawable *> children;
    public:
        geo2d::Shape<int>* shape;
        BaseWidget(int _depthIndex,
                   Point<int> _position,
                   int _width,
                   int _height,
                   Texture *_texture,
                   geo2d::Shape<int>* _shape,
                   int _angle,
                   RendererFlip _flip,
                   rgba<> color);

        BaseWidget(core::Drawable *drawable, geo2d::Shape<int>* _shape);

        BaseWidget(BaseWidget* widget);

        ~BaseWidget();

        /// @brief
        /// That function adds children to widget
        void addChild(core::Drawable *child);
    };
}