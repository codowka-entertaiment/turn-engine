#pragma once

#include <iostream>
#include "SDL_ttf.h"
#include "TurnEngine/wrapper/Font.hpp"
#include "TurnEngine/wrapper/Surface.hpp"
#include "TurnEngine/render/Drawer.hpp"
#include "TurnEngine/core/Object2D.hpp"

namespace TurnEngine::gui {
    /// @brief
    /// Class which represents labels
    class Label : public core::Object2D {
    private:
        std::string text;
        Font *font;
        rgba<> color;
        xy<int> pos;
    public:
        /// @brief
        /// the constructor
        /// @param Font* _font
        /// @param std::string _text
        /// @param xy<int> _pos
        /// @param rgba<> _color
        /// @param int _depthIndex
        /// @param int _angle = 0
        /// @param RendererFlip _flip = RendererFlip::NONE
        Label(
                Font* _font,
                std::string _text,
                xy<int> _pos,
                rgba<> _color,
                int _depthIndex,
                int _angle = 0,
                RendererFlip _flip = RendererFlip::NONE
        );

        /// @brief
        /// method which draws text in label
        /// @param Drawer* drawer
        void draw(render::Drawer *drawer);
    };
}