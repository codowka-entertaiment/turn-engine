#include "Renderer.hpp"

namespace sdl
{
    Renderer::Renderer(const Window &window, int index, Uint32 flags) {
        renderer = SDL_CreateRenderer(window.getWindow(), index, flags);
    }
    Renderer::~Renderer() {
        SDL_DestroyRenderer(renderer);
    }
    int Renderer::setScale(float scaleX, float scaleY) {
        return SDL_RenderSetScale(renderer, scaleX, scaleY);
    }
    std::pair<float, float> Renderer::getScale() {
        std::pair<float, float> scale;
        SDL_RenderGetScale(renderer, &scale.first, &scale.second);
        return scale;
    }
}