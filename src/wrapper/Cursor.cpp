#include "TurnEngine/wrapper/Cursor.hpp"

namespace TurnEngine {

    Cursor::Cursor(std::string path) {
        surface = new Surface(path);
        cursor = SDL_CreateColorCursor(surface->native_handle(), 0, 0);
    }

    void Cursor::enable() {
        SDL_SetCursor(cursor);
    }

}