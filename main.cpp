#include "TurnEngine/Engine.hpp"
#include "TurnEngine/gui/Widget.hpp"
#include <vector>
#include <map>

int line = 0;
int col = 0;
double s_time = 0;
int x = 100;
int y = 100;

using namespace TurnEngine;

std::map<KB_KEYS, bool> keystates;

void move() {
    if (keystates[KB_KEYS::W]) {
        int movement = 10;
        while (movement--) {
            y -= 1;
        }
    }
    if (keystates[KB_KEYS::S]) {
        int movement = 10;
        while (movement--) {
            y += 1;
        }
    }

    if (keystates[KB_KEYS::A]) {
        int movement = 10;
        while (movement--) {
            x -= 1;
        }
    }
    if (keystates[KB_KEYS::D]) {
        int movement = 10;
        while (movement--) {
            x += 1;
        }
    }
}

void Engine::onPollEvents() {
    for (auto const &event: event_queue) {
        if (event.type == SDL_QUIT)
            isQuited = true;
        if (event.type == SDL_MOUSEMOTION) {

        }
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_w) {
                line = 3;
                keystates[KB_KEYS::W] = true;
            } else if (event.key.keysym.sym == SDLK_s) {
                line = 0;
                keystates[KB_KEYS::S] = true;
            } else if (event.key.keysym.sym == SDLK_a) {
                line = 1;
                keystates[KB_KEYS::A] = true;
            } else if (event.key.keysym.sym == SDLK_d) {
                line = 2;
                keystates[KB_KEYS::D] = true;
            }
            keystates[KB_KEYS::NONE] = false;
        }
        if (event.type == SDL_KEYUP) {
            if (event.key.keysym.sym == SDLK_w) {
                keystates[KB_KEYS::W] = false;
            } else if (event.key.keysym.sym == SDLK_s) {
                keystates[KB_KEYS::S] = false;
            } else if (event.key.keysym.sym == SDLK_a) {
                keystates[KB_KEYS::A] = false;
            } else if (event.key.keysym.sym == SDLK_d) {
                keystates[KB_KEYS::D] = false;
            }
            keystates[KB_KEYS::NONE] = true;
        }
    }
}

void Engine::onUpdate() {

}

void Engine::onDraw() {
    Texture *texture = new Texture(*getRenderer(), "../assets/animation.png");
    core::Drawable player
            {
                    2,
                    true,
                    {x, y},
                    64,
                    64,
                    texture,
                    {64 * (col % 4), 64 * (line % 4), 64, 64},
                    0,
                    RendererFlip::NONE
            };
    texture = new Texture(*getRenderer(), "../assets/test.bmp");
    gui::Widget background
            {
                    1,
                    {0, 0},
                    width,
                    height,
                    nullptr,
                    0,
                    RendererFlip::NONE,
                    Color::green
            };
    if (col >= 4) {
        col = 0;
    }
    s_time += 1 / (double) fps;
    if (s_time >= 0.25) {
        s_time = 0;
        if (!keystates[KB_KEYS::NONE]) col += 1;
        move();
    }
    getRenderer()->clear();
    drawer->draw(player);
    drawer->draw(background);
    drawer->renderAll();
    texture->destroy();
}

int main(int, char **) {
    keystates[KB_KEYS::NONE] = true;
    Engine engine{};
    if (!engine.initSDL(SDLInitFlags::EVERYTHING)) {
        return EXIT_FAILURE;
    }
    if (!engine.createWindow("Testing", 1200, 800)) {
        return EXIT_FAILURE;
    }
    if (!engine.createDrawer(RendererFlags::ACCELERATED | RendererFlags::PRESENTVSYNC)) {
        return EXIT_FAILURE;
    }
    engine.start(60);
}