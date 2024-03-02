#include "TurnEngine/TurnEngine.hpp"
#include <vector>

using namespace TurnEngine;

int main(int, char**) {
    SDL2 const sdl(sdl2_init_flags::EVERYTHING);
    if (!sdl)
        return EXIT_FAILURE;
    int W = 800;
    int H = 800;
    window win("TurnEngine", window::pos_centered, {W, H}, window_flags::RESIZABLE);
    if (!win)
        return EXIT_FAILURE;
    renderer ren(win, renderer_flags::ACCELERATED);
    if (!ren)
        return EXIT_FAILURE;
    bool quit = false;
    Uint32 b = 0;
    // main loop
    while (!quit) {
        Uint32 a = SDL_GetTicks();
        if (a - b > 1000 / 60.0) {
            ren.clear();
            b = a;
            // event loop
            for (auto const &event: event_queue) {
                if (event.type == SDL_QUIT)
                    quit = true;
            }
            // update
            // render/draw
            ren.set_draw_color(rgba<>{0xff, 0x00, 0x00, 0xff});
            ren.present();
        }
    }
}