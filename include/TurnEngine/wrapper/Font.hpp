#pragma once

#include <SDL_ttf.h>
#include <string>

namespace TurnEngine {
    class Font {
    private:
        TTF_Font* font;
        int fontSize;
    public:
        Font(const std::string& font, int _fontSize);
        void setFontSize(int _fontSize);
        ~Font();
    };
}