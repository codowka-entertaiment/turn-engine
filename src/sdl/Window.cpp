#include "Window.hpp"

namespace sdl
{

    Window::~Window() {
        SDL_DestroyWindow(window);
    }
    math::VectorInt Window::getWindowSize() {
        math::VectorInt dimensions(0, 0);
        SDL_GetWindowSize(window, &dimensions.x, &dimensions.y);
        return dimensions;
    }
    Surface Window::getWindowSurface() {
        return Surface(SDL_GetWindowSurface(window));
    }
    Window::Window(SDL_Window *window) : window(window) {}
    std::expected<Window, WindowError> Window::init(std::string_view title, const math::Rectangle<int> &rectangle,
                                                    Uint32 flags) {
        SDL_Window *window = SDL_CreateWindow(title.data(), rectangle.vertex().x, rectangle.vertex().y, rectangle.width(),
                                              rectangle.height(), flags);
        if (window != nullptr)
            return Window(window);
        else
            return std::unexpected(WindowError::WindowCreationError);
    }

}