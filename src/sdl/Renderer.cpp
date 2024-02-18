#include "../../include/turn-engine/sdl/Renderer.hpp"

sdl::Renderer::Renderer(SDL_Renderer *renderer) : m_renderer(renderer) {}

sdl::Renderer::~Renderer() {
    SDL_DestroyRenderer(m_renderer);
}

int sdl::Renderer::setScale(float scaleX, float scaleY) {
    return SDL_RenderSetScale(m_renderer, scaleX, scaleY);
}

math::Vector<float> sdl::Renderer::getScale() {
    math::Vector<float> scale(0, 0);
    SDL_RenderGetScale(m_renderer, &scale.x, &scale.y);
    return scale;
}

std::expected<sdl::Renderer, sdl::RendererError> sdl::Renderer::init(const sdl::Window &window, int index, Uint32 flags) {
    SDL_Renderer *renderer = SDL_CreateRenderer(window.m_window, index, flags);
    if (!renderer)
        return std::unexpected(sdl::RendererError::RendererCreationError);
    else {
        return sdl::Renderer(renderer);
    }
}
void sdl::Renderer::copy(sdl::Texture &texture) {
    SDL_RenderCopy(m_renderer, texture.m_texture, nullptr, nullptr);
}
void sdl::Renderer::clear() {
    SDL_RenderClear(m_renderer);
}
void sdl::Renderer::present() {
    SDL_RenderPresent(m_renderer);
}
