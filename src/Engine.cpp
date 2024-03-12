#include "TurnEngine/Engine.hpp"

namespace TurnEngine {
    bool Engine::initSDL(SDLInitFlags sdl_flags, int audioFlags) {
        SDL2 const sdl(sdl_flags);
        if (!sdl)
            return false;
        TTF_Init();
        Audio::init(audioFlags);
        return true;
    }

    bool Engine::openAudio() {
        return Audio::open();
    }

    bool Engine::createWindow(const std::string &title, WindowFlags flags, int width, int height) {
        this->height = height;
        this->width = width;
        this->window = new Window("TurnEngine", Window::pos_centered, {width, height}, flags);
        if (this->window == nullptr)
            return false;
        this->height = this->window->size().height;
        this->width = this->window->size().width;
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
            getRenderer()->set_draw_color(Color::black);
            getRenderer()->clear();
            onDraw();
            this->ticks = currentTicks;
            getRenderer()->present();
            currentTicks++;
        }
    }

    void Engine::start(int fps) {
        this->currentTicks = 0;
        this->ticks = 0;
        this->fps = fps;
        while (!isQuited) {
            if (currentTicks > fps) currentTicks = 1;
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
        TTF_Quit();
        Audio::close();
        Mix_Quit();
        IMG_Quit();
        SDL_Quit();
    }

    int Engine::getHeight() {
        return this->height;
    }

    int Engine::getWidth() {
        return this->width;
    }
}