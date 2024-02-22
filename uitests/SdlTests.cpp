#include "../include/turn-engine/sdl/Renderer.hpp"
#include "../include/turn-engine/sdl/SDL.hpp"
#include "../include/turn-engine/sdl/Surface.hpp"
#include "../include/turn-engine/sdl/Texture.hpp"
#include "../include/turn-engine/sdl/Window.hpp"
#include <turn-engine/sdl/Rect.hpp>


int main()
{
    sdl::SDLLibInit(SDL_INIT_EVERYTHING,0);
    auto window = sdl::Window::init("test", geo2d::RectangleInt::init_uncheck(geo2d::PositionInt(0,0),800,600),0);
    auto renderer = sdl::Renderer::init(window.value(),-1,0);
    auto surface = sdl::Surface::load("picture.jpg");
    auto texture = sdl::Texture::init(renderer.value(),surface.value());
    renderer->clear();
    renderer->copy(texture.value());
    renderer->copy(texture.value(),sdl::Rect(geo2d::VectorInt(500,500),500,500),sdl::Rect(geo2d::VectorInt(100,100),500,500));
    renderer->copy(texture.value(),sdl::Rect(geo2d::VectorInt(25,25),50,50));
    renderer->present();
    while(1);
    return 0;
}
