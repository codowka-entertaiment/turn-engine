#include "../include/turn-engine/sdl/Renderer.hpp"
#include "../include/turn-engine/sdl/SDL.hpp"
#include "../include/turn-engine/sdl/Surface.hpp"
#include "../include/turn-engine/sdl/Texture.hpp"
#include "../include/turn-engine/sdl/Window.hpp"


int main()
{
    sdl::SDLLibInit(SDL_INIT_EVERYTHING,0);
    auto window = sdl::Window::init("test", math::RectangleInt::init_uncheck(math::PositionInt(0,0),800,600),0);
    auto renderer = sdl::Renderer::init(window.value(),-1,0);
    auto surface = sdl::Surface::load("picture.jpg");
    auto texture = sdl::Texture::init(renderer.value(),surface.value());
    renderer->clear();
    renderer->copy(texture.value());
    renderer->present();
    while(1);
    return 0;
}
