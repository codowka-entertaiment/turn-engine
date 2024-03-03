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

    void Engine::poll() {
        Uint32 currentTicks = SDL_GetTicks();
        onPollEvents();
        onUpdate();
        if (currentTicks - this->ticks > 1000 / this->fps) {
            onDraw();
            getRenderer()->clear();
            this->ticks = currentTicks;
            getRenderer()->present();
        }
    }

    void Engine::start() {
        this->ticks = 0;
        this->fps = 60;
        while (!isQuited) {
            poll();
        }
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

    Engine::~Engine() {
        window->destroy();
        drawer->destroy();
    }
}