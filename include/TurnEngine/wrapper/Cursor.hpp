#pragma once

#include <iostream>

#include "SDL2/SDL.h"
#include "TurnEngine/wrapper/Surface.hpp"

namespace TurnEngine {

    /// @brief
    /// That class wraps SDL_Cursor
    class Cursor {
    private:
        SDL_Cursor *cursor;
        Surface *surface;
    public:
        Cursor(std::string path);

        /// @brief
        /// That method enables loaded cursor
        void enable();
    };
}