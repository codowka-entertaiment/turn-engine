#pragma once

#include "wrapper/Color.hpp"
#include "wrapper/Enums.hpp"
#include "wrapper/Event.hpp"
#include "wrapper/Init.hpp"
#include "wrapper/MessageBox.hpp"
#include "wrapper/Pixel.hpp"
#include "wrapper/Renderer.hpp"
#include "wrapper/Shapes.hpp"
#include "wrapper/Surface.hpp"
#include "wrapper/Texture.hpp"
#include "wrapper/Utils.hpp"
#include "wrapper/Window.hpp"

#include "ext/Math.hpp"

#include "core/Object.hpp"
#include "core/Object2D.hpp"
#include "core/Observer.hpp"
#include "core/Subject.hpp"
#include "core/Responsible.hpp"
#include "core/event/Event.hpp"
#include "core/event/Command.hpp"

#include "render/Drawer.hpp"

namespace TurnEngine {
    class Engine {
    private:
        Window* window;
        render::Drawer* drawer;
        int fps;
        int currentFrame;
        Uint32 ticks;
        void poll();
        bool isQuited;
        int height;
        int width;
    public:
        ~Engine();
        bool initSDL(SDLInitFlags sdl_flags);
        bool createWindow(const std::string& title, int width = 800, int height = 600);
        bool createDrawer(RendererFlags renderer_init_flags);
        void onPollEvents();
        void onUpdate();
        void onDraw();
        void start(int fps = 60);
        Window* getWindow();
        Renderer* getRenderer();
        render::Drawer* getDrawer();
        int getHeight();
        int getWidth();
    };
}