#include "Window.hpp"

namespace sdl
{

    //todo: wait while rectangle will be fixed and make window work on it
    Window::Window(std::string_view title, const math::Rectangle<int> &rectangle, Uint32 flags) {
        // window = SDL_CreateWindow(title.data(), rectangle., y, w, h, flags);
    }
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

}