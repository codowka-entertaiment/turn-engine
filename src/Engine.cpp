#include "TurnEngine/Engine.hpp"


namespace TurnEngine {
    bool Engine::initSDL(SDLInitFlags sdl_flags) {
        SDL2 const sdl(SDLInitFlags::EVERYTHING);
        if (!sdl)
            return false;
        return true;
    }

    bool Engine::createWindow(const std::string &title, int width, int height) {
        this->window = new Window("TurnEngine", Window::pos_centered, {width, height}, WindowFlags::RESIZABLE);
        if (this->window == nullptr)
            return false;
        return true;
    }

    bool Engine::createDrawer(RendererFlags renderer_init_flags) {
        this->drawer = new render::Drawer(new Renderer(*(this->window), renderer_init_flags));
        if (this->drawer == nullptr)
            return false;
        return true;
    }

    Window* Engine::getWindow() {
        return this->window;
    }

    Renderer* Engine::getRenderer() {
        return this->drawer->getRenderer();
    }

    render::Drawer* Engine::getDrawer() {
        return this->drawer;
    }
}