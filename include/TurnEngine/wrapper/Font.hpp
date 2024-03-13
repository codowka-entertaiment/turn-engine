#pragma once

#include <SDL_ttf.h>
#include <string>
#include "TurnEngine/wrapper/Surface.hpp"

namespace TurnEngine {
    /// @brief
    /// That class wraps TTF_Font
    class Font {
    public:
        TTF_Font *font;
        int fontSize;

        Font(const std::string &font, int _fontSize);

        /// @brief
        /// That method sets font size
        void setFontSize(int _fontSize);

        ~Font();
    };

    /// @brief
    /// That function renders text at fast quality to a new 8-bit surface
    Surface *renderSolid(Font *font, const std::string &text, rgba<> color);

    /// @brief
    /// That function renders text at high quality to a new ARGB surface.
    Surface *renderBlended(Font *font, const std::string &text, rgba<> color);

    /// @brief
    /// That function renders text at high quality to a new 8-bit surface with background color.
    Surface *renderShaded(Font *font, const std::string &text, rgba<> foreground, rgba<> background);
}