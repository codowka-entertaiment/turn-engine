#include <turn-engine/sdl/Renderer.hpp>

sdl::Renderer::Renderer(SDL_Renderer *renderer) : m_renderer(renderer) {}

sdl::Renderer::~Renderer() { SDL_DestroyRenderer(m_renderer); }

int sdl::Renderer::setScale(float scaleX, float scaleY) {
    return SDL_RenderSetScale(m_renderer, scaleX, scaleY);
}

geo2d::Vector<float> sdl::Renderer::getScale() {
    geo2d::Vector<float> scale(0, 0);
    SDL_RenderGetScale(m_renderer, &scale.x, &scale.y);
    return scale;
}

std::expected<sdl::Renderer, sdl::RendererError>
sdl::Renderer::init(const sdl::Window &window, int index, Uint32 flags) {
    SDL_Renderer *renderer = SDL_CreateRenderer(window.m_window, index, flags);
    if (!renderer)
        return std::unexpected(sdl::RendererError::RendererCreationError);
    else {
        return sdl::Renderer(renderer);
    }
}

void sdl::Renderer::copy(
    sdl::Texture &texture,
    const sdl::Rect &srcrect,
    const sdl::Rect &dstrect
) {
    SDL_Rect a, b;
    a = srcrect;
    b = dstrect;
    SDL_RenderCopy(m_renderer, texture.m_texture, (&a), (&b));
}

void sdl::Renderer::clear() { SDL_RenderClear(m_renderer); }

void sdl::Renderer::present() { SDL_RenderPresent(m_renderer); }

sdl::Renderer::Renderer(sdl::Renderer &&other) noexcept {
    m_renderer = other.m_renderer;
    other.m_renderer = nullptr;
}

sdl::Renderer::Renderer(const sdl::Renderer &other)
    : m_renderer(other.m_renderer) {}

void sdl::Renderer::copy(sdl::Texture &texture, const sdl::Rect &dstrect) {
    SDL_Rect a = dstrect;
    SDL_RenderCopy(m_renderer, texture.m_texture, nullptr, (&a));
}

void sdl::Renderer::copy(sdl::Texture &texture) {
    SDL_RenderCopy(m_renderer, texture.m_texture, nullptr, nullptr);
}
