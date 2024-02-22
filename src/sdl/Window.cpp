#include <turn-engine/sdl/Window.hpp>

sdl::Window::~Window() { SDL_DestroyWindow(m_window); }

geo2d::VectorInt sdl::Window::getSize() {
    geo2d::Vector<int> dimensions(0, 0);
    SDL_GetWindowSize(m_window, &dimensions.x, &dimensions.y);
    return dimensions;
}

sdl::Surface sdl::Window::getSurface() {
    return Surface(SDL_GetWindowSurface(m_window));
}

sdl::Window::Window(SDL_Window *window) : m_window(window) {}
std::expected<sdl::Window, sdl::WindowError> sdl::Window::init(
    std::string_view title,
    const geo2d::Rectangle<int> &rectangle,
    Uint32 flags
) {
    SDL_Window *window = SDL_CreateWindow(
        title.data(),
        rectangle.vertex().x,
        rectangle.vertex().y,
        rectangle.width(),
        rectangle.height(),
        flags
    );
    if (window != nullptr)
        return Window(window);
    else
        return std::unexpected(WindowError::WindowCreationError);
}

sdl::Window::Window(sdl::Window &&other) noexcept {
    m_window = other.m_window;
    other.m_window = nullptr;
}

sdl::Window::Window(const sdl::Window &other) : m_window(other.m_window) {}

void sdl::Window::setIcon(std::string_view filename) {
    auto icon = Surface::load(filename);
    SDL_SetWindowIcon(m_window, icon->m_surface);
}

void sdl::Window::raise() {
    SDL_FlashWindow(m_window, SDL_FLASH_UNTIL_FOCUSED);
    SDL_RaiseWindow(m_window);
}
