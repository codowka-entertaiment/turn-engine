#pragma once

#include <memory>
#include "../math/Vector.hpp"
#include "SDL.h"
#include "Window.hpp"
#include "sdl/Texture.hpp"

namespace sdl
{
    enum class RendererError : std::uint8_t { WindowDestroyed };
    class Renderer {
        friend class Texture;

    private:
        SDL_Renderer *renderer;
        std::shared_ptr<Window> window;
        Renderer(const std::weak_ptr<Window> &window, SDL_Renderer *renderer);

    public:
        static std::expected<Renderer, RendererError> init(const std::shared_ptr<Window> &window, int index, Uint32 flags);
        int setScale(float scaleX, float scaleY);
        math::Vector<float> getScale();
        ~Renderer();
    };
}