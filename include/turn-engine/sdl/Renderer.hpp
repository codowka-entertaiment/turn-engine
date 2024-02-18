#pragma once

#include "../math/Vector.hpp"
#include "Texture.hpp"
#include "Renderer.hpp"
#include "Window.hpp"

namespace sdl
{
    enum class RendererError { RendererCreationError };
    class Window;
    class Texture;
    class Renderer {
        friend class Texture;

    private:
        SDL_Renderer *m_renderer;
        explicit Renderer(SDL_Renderer *renderer);

    public:
        Renderer(const Renderer& other);
        Renderer(Renderer&& other) noexcept;
        static std::expected<Renderer, RendererError> init(const Window &window, int index, Uint32 flags);
        int setScale(float scaleX, float scaleY);
        math::Vector<float> getScale();
        void copy(Texture &texture);
        void clear();
        void present();
        ~Renderer();
    };
}