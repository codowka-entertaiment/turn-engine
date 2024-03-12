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
#include "wrapper/Cursor.hpp"
#include "wrapper/Audio.hpp"

#include "ext/Math.hpp"

#include "core/Responsible.hpp"
#include "core/Object2D.hpp"
#include "core/Area2D.hpp"
#include "core/Scene.hpp"
#include "core/Event.hpp"

#include "render/Drawer.hpp"

#include "gui/BaseButton.hpp"
#include "gui/Sprite.hpp"
#include "gui/Label.hpp"

#include "geo2d/Shapes.hpp"
#include "geo2d/Vector.hpp"

namespace TurnEngine {
    class Engine {
    private:
        Window* window;
        render::Drawer* drawer;
        int fps;
        int currentTicks;
        Uint32 ticks;
        void poll();
        bool isQuited;
        int height;
        int width;
    public:
        ~Engine();
        bool initSDL(SDLInitFlags sdl_flags, int audioFlags = MIX_INIT_WAVPACK | MIX_INIT_OPUS | MIX_INIT_OGG | MIX_INIT_MP3 | MIX_INIT_MOD | MIX_INIT_MID | MIX_INIT_FLAC);
        bool openAudio();
        bool createWindow(const std::string& title, WindowFlags flags, int width = 800, int height = 600);
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