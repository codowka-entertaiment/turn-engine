#include "Window.hpp"

namespace sdl
{
    Window::Window(std::string_view title, int x, int y, int w, int h,
                   Uint32 flags) {
        window = SDL_CreateWindow(title.data(), x, y, w, h, flags);
    }
    Window::~Window() {
        SDL_DestroyWindow(window);
    }
    SDL_Window *Window::getWindow() const {
        return window;
    }
    math::Dimensions2i Window::getWindowSize() {
        math::Dimensions2i dimensions(0, 0);
        SDL_GetWindowSize(window, &dimensions.x, &dimensions.y);
        return dimensions;
    }
    SDL_Surface *Window::getWindowSurface() {
        return SDL_GetWindowSurface(window);
    }
}