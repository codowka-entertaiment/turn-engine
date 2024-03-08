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

    Surface* renderSolid(Font* font, const std::string& text, rgba<> color) {
        return new Surface(TTF_RenderUTF8_Solid(font->font, text.c_str(), color));
    }

    Surface* renderBlended(Font* font, const std::string& text, rgba<> color) {
        return new Surface(TTF_RenderUTF8_Blended(font->font, text.c_str(), color));
    }

    Surface* renderShaded(Font* font, const std::string& text, rgba<> foreground, rgba<> background) {
        return new Surface(TTF_RenderUTF8_Shaded(font->font, text.c_str(), foreground, background));
    }
}