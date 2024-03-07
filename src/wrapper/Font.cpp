#include "TurnEngine/wrapper/Font.hpp"

namespace TurnEngine {

    constexpr Font::Font(const std::string& _font, int _fontSize) {
        font = TTF_OpenFont(_font.c_str(), _fontSize);
    }

    constexpr Font::~Font() {
        TTF_CloseFont(font);
    }

    constexpr void Font::setFontSize(int _fontSize) {
        TTF_SetFontSize(font, _fontSize);
    }

    Surface* renderSolid(Font* font, const std::string& text, rgba<> color) {
        return new Surface(TTF_RenderText_Solid(font->font, text.c_str(), color));
    }

    Surface* renderBlended(Font* font, const std::string& text, rgba<> color) {
        return new Surface(TTF_RenderText_Blended(font->font, text.c_str(), color));
    }

    Surface* renderShaded(Font* font, const std::string& text, rgba<> foreground, rgba<> background) {
        return new Surface(TTF_RenderText_Shaded(font->font, text.c_str(), foreground, background));
    }
}