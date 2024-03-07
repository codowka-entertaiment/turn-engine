#include "TurnEngine/wrapper/Font.hpp"

namespace TurnEngine {

    Font::Font(const std::string& _font, int _fontSize) {
        font = TTF_OpenFont(_font.c_str(), _fontSize);
    }

    Font::~Font() {
        TTF_CloseFont(font);
    }

    void Font::setFontSize(int _fontSize) {
        TTF_SetFontSize(font, _fontSize);
    }
}