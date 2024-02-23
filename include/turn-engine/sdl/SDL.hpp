#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "Rect.hpp"
#include "Renderer.hpp"
#include "Surface.hpp"
#include "Texture.hpp"
#include "Window.hpp"

namespace sdl
{
    ///sdl_init - инициализация билиотек SDL
    /// \param SDLFlags - флаги для библиотеки SDL
    /// \param SDLIMGFlags - флаги для библииотеки SDLImage
    /// \return возращает 0 при успешной инициализации -1 при ошибке
    int sdl_init(Uint32 SDLFlags, int SDLIMGFlags);
    ///Очистка библиотек SDL
    void sdl_close();
}
