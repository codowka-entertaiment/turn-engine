#pragma once

#include <iostream>
#include "SDL_ttf.h"
#include "TurnEngine/wrapper/Font.hpp"
#include "TurnEngine/wrapper/Surface.hpp"
#include "TurnEngine/render/Drawer.hpp"

namespace TurnEngine::gui {
    class Label {
    private:
        std::string text;
        Font* font;
        Texture* txr;
        rgba<> color;
        xy<int> pos;
    public:
        Label(std::string _text, xy<int> _pos, rgba<> _color);
        void draw(render::Drawer* drawer);
    };
}