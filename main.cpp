#include "TurnEngine/Engine.hpp"
#include <vector>

using namespace TurnEngine;

void Engine::onPollEvents() {
    for (auto const &event: event_queue) {
        if (event.type == SDL_QUIT)
            isQuited = true;
        if (event.type == SDL_MOUSEMOTION) {

        }
    }
}

void Engine::onUpdate() {

}

void Engine::onDraw() {
    drawer->getRenderer()->set_draw_color(Color::white);
    std::vector<Point<int>> points;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            points.emplace_back(i, j);
        }
    }
    drawer->drawPoints(points);
}

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
    engine.start();
}