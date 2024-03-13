#pragma once

#include "TurnEngine/core/Object2D.hpp"
#include "TurnEngine/core/Subject.hpp"
#include "TurnEngine/geo2d/shapes/Shape.hpp"
#include "TurnEngine/gui/Label.hpp"

namespace TurnEngine::gui {
    /// @brief
    /// Class represents base button class
    class BaseButton : public core::Object2D {
    private:
        Texture *commonTexture;
        Texture *onHover;
        std::function<void()> handler;
        std::string text;
        Label* label;
        void emptyFunc() {};
    public:
        /// @brief
        /// the constructor
        /// @param geo2d::Shape<int> *_shape
        /// @param int _depthIndex
        /// @param Point<int> _position
        /// @param int _width
        /// @param int _height
        /// @param Texture *_commonTexture
        /// @param Texture *_onHoverTexture
        /// @param int _angle
        /// @param RendererFlip _flip
        /// @param rgba<> color
        /// @param std::string _text
        /// @param std::string _font
        /// @param int _fontSize
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

        /// @brief
        /// method calls handler on event
        /// @param Event* _event
        void update(core::Event* _event) override;

        /// @brief
        /// method draws button and text inside it
        /// @param Drawer* drawer
        void draw(render::Drawer* drawer) override;

        /// @brief
        /// button handler setter
        /// @param std::function<void(void)> _func
        void setHandler(std::function<void(void)> _func);

    };
}