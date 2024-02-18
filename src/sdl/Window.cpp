#include "../../include/turn-engine/sdl/Window.hpp"

sdl::Window::~Window() {
    SDL_DestroyWindow(m_window);
}
math::VectorInt sdl::Window::getWindowSize() {
    math::VectorInt dimensions(0, 0);
    SDL_GetWindowSize(m_window, &dimensions.x, &dimensions.y);
    return dimensions;
}
sdl::Surface sdl::Window::getWindowSurface() {
    return Surface(SDL_GetWindowSurface(m_window));
}
sdl::Window::Window(SDL_Window *window) : m_window(window) {}
std::expected<sdl::Window, sdl::WindowError> sdl::Window::init(std::string_view title, const math::Rectangle<int> &rectangle,
                                                               Uint32 flags) {
    SDL_Window *window = SDL_CreateWindow(title.data(), rectangle.vertex().x, rectangle.vertex().y, rectangle.width(),
                                          rectangle.height(), flags);
    if (window != nullptr)
        return Window(window);
    else
        return std::unexpected(WindowError::WindowCreationError);
}