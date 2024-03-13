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
        Window *window;
        render::Drawer *drawer;
        int fps;
        int currentTicks;
        Uint32 ticks;

        void poll();

        bool isQuited;
        int height;
        int width;
    public:
        ~Engine();

        /// @brief
        /// initSDL method inits SDL library and all its extensions
        /// @return
        /// Returns `true` if initialized successfully, else `false`
        bool initSDL(SDLInitFlags sdl_flags,
                     int audioFlags = MIX_INIT_WAVPACK | MIX_INIT_OPUS | MIX_INIT_OGG | MIX_INIT_MP3 | MIX_INIT_MOD |
                                      MIX_INIT_MID | MIX_INIT_FLAC);

        /// @brief
        /// That method opens audio device
        /// @return
        /// Boolean `true` if opened successfully, else `false`
        bool openAudio();

        /// @brief
        /// That method creates main window
        /// @return
        /// Boolean `true` if created successfully, else `false`
        bool createWindow(const std::string &title, WindowFlags flags, int width = 800, int height = 600);

        /// @brief
        /// That method creates Drawer and Renderer
        /// @return
        /// Boolean `true` if created successfully, else `false`
        bool createDrawer(RendererFlags renderer_init_flags);

        /// @brief
        /// Engine user method.
        /// Stands for polling and processing events such as mouse or keyboard events.
        /// Must be implemented by user
        void onPollEvents();

        /// @brief
        /// Engine user method.
        /// Stands for updating game objects.
        /// Must be implemented by user
        void onUpdate();

        /// @brief
        /// Engine user method.
        /// Stands for drawing game objects.
        /// Must be implemented by user
        void onDraw();

        /// @brief
        /// That mehod starts game main loop
        void start(int fps = 60);

        /// @brief
        /// That func returns main window
        Window *getWindow();

        /// @brief
        /// That func returns hardware renderer
        Renderer *getRenderer();

        /// @brief
        /// That func returns engine drawer
        render::Drawer *getDrawer();

        /// @brief
        /// That func returns main window height
        int getHeight();

        /// @brief
        /// That func returns main window width
        int getWidth();
    };
}