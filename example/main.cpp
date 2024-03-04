#include "TurnEngine/Engine.hpp"
#include "TurnEngine/gui/Widget.hpp"

using namespace TurnEngine;

void Engine::onPollEvents() {
    for (auto event: event_queue) {
        if (event.type == SDL_QUIT) {
            isQuited = true;
        }
        if (event.type == SDL_USEREVENT) {
            // Handle user event
        }
        if (event.type == SDL_KEYDOWN) {
            // Handle keyboard pressed buttons
        }
        if (event.type == SDL_KEYUP) {
            // Handle keyboard release buttons
        }
        if (event.type == SDL_MOUSEMOTION) {
            // Handle mouse motion inside window
            printf("Moved: x:%d y:%d\n", event.motion.x, event.motion.y);
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            // Handle mouse button click
            if (event.button.button == SDL_BUTTON_LEFT) {
                printf("LMB DOWN: x:%d y:%d\n", event.button.x, event.motion.y);
            }
            if (event.button.button == SDL_BUTTON_RIGHT) {
                printf("RMB DOWN: x:%d y:%d\n", event.button.x, event.motion.y);
            }
        }
        if (event.type == SDL_MOUSEBUTTONUP) {
            // Handle mouse button release
            if (event.button.button == SDL_BUTTON_LEFT) {
                printf("LMB UP: x:%d y:%d\n", event.button.x, event.motion.y);
            }
            if (event.button.button == SDL_BUTTON_RIGHT) {
                printf("RMB UP: x:%d y:%d\n", event.button.x, event.motion.y);
            }
        }
    }
}

void Engine::onUpdate() {

}

void Engine::onDraw() {
    Uint32 start = SDL_GetTicks();
    if (start - currentTicks > 1000 / fps) {
        currentTicks = start;
    }
}

int main(int, char **) {
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

    // Create subjects

    auto *subject = new core::Subject;
    auto *subject1 = new core::Subject;

    // Observers are subscribing subjects

    auto *observer1 = new core::Observer();
    observer1->subscribe(subject);
    observer1->subscribe(subject1);
    auto *observer2 = new core::Observer();
    observer2->subscribe(subject);
    observer2->subscribe(subject1);
    observer2->unsubscribe(subject);
    auto *observer3 = new core::Observer();
    observer3->subscribe(subject);

    // Subjects send signal
    subject->signal("click");
    subject1->signal("jump");
//    engine.start(60);
}