#include "turn-engine/sdl/SDL.hpp"

int main() {
    sdl::SDLInit(SDL_INIT_EVERYTHING, 0);

    auto window = sdl::Window::init("test", geo2d::RectangleInt::init_uncheck(geo2d::PositionInt(0, 0), 800, 600), 0);

    auto renderer = sdl::Renderer::init(window.value(), -1, 0);
    auto surface = sdl::Surface::load("picture.jpg");
    auto texture = sdl::Texture::init(renderer.value(), surface.value());

    renderer->clear();
    renderer->copy(texture.value());

    renderer->copy(texture.value(), sdl::Rect(geo2d::VectorInt(500, 500), 500, 500),
                   sdl::Rect(geo2d::VectorInt(100, 100), 500, 500));

    renderer->copy(texture.value(), sdl::Rect(geo2d::VectorInt(25, 25), 50, 50));

    renderer->present();
    //todo: add event loop
    while (true) {}
    sdl::SDLClose();
}
