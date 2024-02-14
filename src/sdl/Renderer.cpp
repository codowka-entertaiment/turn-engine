#include "Renderer.hpp"

namespace sdl
{
    Renderer::~Renderer() {
        SDL_DestroyRenderer(renderer);
    }
    int Renderer::setScale(float scaleX, float scaleY) {
        return SDL_RenderSetScale(renderer, scaleX, scaleY);
    }
    
    math::Vector<float> Renderer::getScale() {
        math::Vector<float> scale(0, 0);
        SDL_RenderGetScale(renderer, &scale.x, &scale.y);
        return scale;
    }
    std::expected<Renderer, RendererError> Renderer::init(const std::shared_ptr<Window> &window, int index, Uint32 flags) {
        if (!window)
            return Renderer(window, SDL_CreateRenderer(window->getWindow(), index, flags));
        else
            return std::unexpected(RendererError::WindowDestroyed);
    }
    Renderer::Renderer(const std::weak_ptr<Window> &window, SDL_Renderer *renderer) : window(window), renderer(renderer) {}
}