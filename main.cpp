#include "TurnEngine/TurnEngine.hpp"
#include <vector>

using namespace TurnEngine;

int main(int, char**) {
    SDL2 const sdl(SDLInitFlags::EVERYTHING);
    if (!sdl)
        return EXIT_FAILURE;
    int W = 800;
    int H = 800;
    Window win("TurnEngine", Window::pos_centered, {W, H}, WindowFlags::RESIZABLE);
    if (!win)
        return EXIT_FAILURE;
    Renderer ren(win, RendererFlags::ACCELERATED | RendererFlags::PRESENTVSYNC);
    Texture *text = new Texture(ren, "../assets/test1.png");
    Rect<int> player = {W / 2, H / 2, 50, 50};
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
                if (event.type == SDL_MOUSEMOTION) {
                    player.x() = event.motion.x - player.w() / 2;
                    player.y() = event.motion.y - player.h() / 2;
                }
            }
            // update
            // render/draw
            ren.set_draw_color(rgba<>{0xff, 0x00, 0x00, 0xff});
            ren.copy_ex(player, *text, 0);
            ren.present();
        }
    }
}