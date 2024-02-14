#pragma once

#include <cinttypes>
#include <expected>
#include "SDL.h"
#include "SDL_image.h"
#include "sdl/Renderer.hpp"
#include "sdl/Surface.hpp"

namespace sdl
{
    enum class TextureError : std::uint8_t { CantLoadTexture };
    class Texture {
    private:
        SDL_Texture *texture;
        explicit Texture(SDL_Texture *texture);

    public:
        static std::expected<Texture, TextureError> init(Renderer *renderer, Surface *surface);
        ~Texture();
    };
}