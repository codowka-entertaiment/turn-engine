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

int func(int x) {
    return sqrt(pow(100, 2) - pow(x, 2));
}

int func1(int x) {
    return x * sin(1 / (3.14 / 180 * (x - 50)));
}

void Engine::onDraw() {
    std::vector<Point<int>> points;
    for (int i = -100; i < getWidth(); i++) {
        points.emplace_back(i + 1100, func(i) + height / 2 + 100);
    }
    drawer->drawPoints(points, Color::yellow);
    for (int i = -100; i < getWidth(); i++) {
        points.emplace_back(i + 1100, -func(i) + height / 2 + 100);
    }
    drawer->drawPoints(points, Color::yellow);
    for (int i = -100; i < getWidth(); i++) {
        points.emplace_back(i + 1100, func(i) + height / 2 - 100);
    }
    drawer->drawPoints(points, Color::yellow);
    for (int i = -100; i < getWidth(); i++) {
        points.emplace_back(i + 1100, -func(i) + height / 2 - 100);
    }
    drawer->drawPoints(points, Color::yellow);
    for (int i = 0; i < getWidth(); i++) {
        points.emplace_back(i, -(func1(i)) + height / 2);
    }
    drawer->drawPoints(points, Color::yellow);
    for (int i = 0; i < getWidth(); i++) {
        points.emplace_back(i, (func1(i)) + height / 2);
    }
    drawer->drawPoints(points, Color::yellow);
}

int main(int, char**) {
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
    engine.start();
}