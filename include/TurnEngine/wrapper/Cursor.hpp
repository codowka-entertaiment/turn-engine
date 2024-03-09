#pragma once

#include <iostream>

#include "SDL2/SDL.h"
#include "TurnEngine/wrapper/Surface.hpp"

namespace TurnEngine {
    class Cursor {
    private:
        SDL_Cursor* cursor;
        Surface* surface;
    public:
        Cursor(std::string path);
        void enable();
    };
}