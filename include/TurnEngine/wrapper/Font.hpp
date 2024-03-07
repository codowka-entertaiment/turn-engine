#pragma once

#include <SDL_ttf.h>
#include <string>
#include "TurnEngine/wrapper/Surface.hpp"

namespace TurnEngine {
    class Font {
    public:
        TTF_Font* font;
        int fontSize;
        constexpr Font(const std::string& font, int _fontSize);
        constexpr void setFontSize(int _fontSize);
        constexpr ~Font();
    };
    Surface* renderSolid(Font* font, const std::string& text, rgba<> color);
    Surface* renderBlended(Font* font, const std::string& text, rgba<> color);
    Surface* renderShaded(Font* font, const std::string& text, rgba<> foreground, rgba<> background);
}