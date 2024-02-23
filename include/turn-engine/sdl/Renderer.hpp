#pragma once

#include "turn-engine/geo2d/Shapes.hpp"
#include "turn-engine/geo2d/Vector.hpp"

#include "Rect.hpp"
#include "Texture.hpp"
#include "Window.hpp"

namespace sdl
{
    class Window;
    class Texture;

    enum class RendererError { RendererCreationError };

    class Renderer {
        friend class Texture;

    private:
        SDL_Renderer *m_renderer;
        explicit Renderer(SDL_Renderer *renderer);

    public:
        Renderer(const Renderer &other);
        Renderer(Renderer &&other) noexcept;

        ~Renderer();

        static std::expected<Renderer, RendererError> init(const Window &window, int index, Uint32 flags);

        /// setScale - устанавливает параметр масштабирования для рендера
        /// \param scaleX
        /// \param scaleY
        /// \return  возвращает 0 при успешной установке масштабирования. отрицательную ошибку в ином случае
        int setScale(float scaleX, float scaleY);

        /// getScale
        /// \return возращает вектор текущего масшабирования ренедра
        geo2d::Vector<float> getScale();

        /// copy - копирует часть текстуры в определенное место цели рендеринга.
        /// \param texture - передаваемая текстура
        /// \param srcrect - квадрат исходной текстуры(основная цель - создание анимаций из спрайтлиста)
        /// \param dstrect - квадрат положения текстуры в цели рендеринга
        void copy(Texture &texture, const sdl::Rect &srcrect, const sdl::Rect &dstrect);

        /// copy - копирует текстуру в определенное место цели рендеринга.
        /// \param texture - передаваемая текстура
        /// \param dstrect - квадрат положения текстуры в цели рендеринга
        void copy(Texture &texture, const sdl::Rect &dstrect);

        /// copy - копирует и растягивает текстуру на всю площадь цели рендеринга.
        /// \param texture - передаваемая текстура
        void copy(Texture &texture);

        ///clear - очищает текущую цель ренедра
        void clear();

        ///present - обновдяет экран
        void present();
    };
}