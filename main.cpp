#include "TurnEngine/Engine.hpp"
#include <vector>

using namespace TurnEngine;

int main(int, char**) {
    Engine engine{};
    if (!engine.initSDL(SDLInitFlags::EVERYTHING)) {
        return EXIT_FAILURE;
    }
    if (!engine.createWindow("Testing", 800, 600)) {
        return EXIT_FAILURE;
    }
    if (!engine.createDrawer(RendererFlags::ACCELERATED | RendererFlags::PRESENTVSYNC)) {
        return EXIT_FAILURE;
    }
    Renderer* ren = engine.getRenderer();

    bool quit = false;
    Uint32 b = 0;
    // main loop
    while (!quit) {
        Uint32 a = SDL_GetTicks();
        if (a - b > 1000 / 60.0) {
            ren->clear();
            b = a;
            // event loop
            for (auto const &event: event_queue) {
                if (event.type == SDL_QUIT)
                    quit = true;
                if (event.type == SDL_MOUSEMOTION) {
                    ren->set_draw_color(rgba<>{0xff, 0x00, 0x00, 0xff});
                } else {
                    ren->set_draw_color(rgba<>{0x00, 0x00, 0x00, 0xff});
                }
            }
            // update
            // render/draw
            ren->present();
        }
    }
}