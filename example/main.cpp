#include "TurnEngine/Engine.hpp"
#include <vector>

using namespace TurnEngine;
gui::Sprite *tile;

// Define that method to handle events
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
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            // Handle mouse button click
            if (event.button.button == SDL_BUTTON_LEFT) {
                printf("LMB DOWN: x:%d y:%d\n", event.button.x, event.motion.y);
//                geo2d::PositionInt pos{event.motion.x, event.motion.y};
//                for (int i = 0; i < map.size(); i++) {
//                    if (map[i]->shape->contains(pos)) {
//                        map[i]->texture = texture2;
//                    }
//                }
            }
            if (event.button.button == SDL_BUTTON_RIGHT) {
                printf("RMB DOWN: x:%d y:%d\n", event.button.x, event.motion.y);
//                geo2d::PositionInt pos{event.motion.x, event.motion.y};
//                for (int i = 0; i < map.size(); i++) {
//                    if (map[i]->shape->contains(pos)) {
//                        map[i]->texture = texture1;
//                    }
//                }
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

// Define that method to implement game logic, which updates state of your game
void Engine::onUpdate() {
}

// Define that method to implement drawer logic (IDK somebody try to use it with threads)
void Engine::onDraw() {
    gui::Label *label = new gui::Label(new Font("../example/assets/Roboto-Black.ttf", 30), "Леша шагает", {100, 100}, Color::white, 5);
    label->draw(getDrawer());
    tile->draw(getDrawer());
    getDrawer()->renderAll();
}

// Steps to launch game
// 1. Initialize Engine class
// 2. Call initSDL method
// 3. Call createWindow method
// 4. Call createDrawer method
// 5. Call start method
int launchGame() {
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
    auto texture = new Texture(*engine.getRenderer(), "../example/assets/animation.png");
    auto query = texture->query();
    tile = new gui::Sprite(0,
                           true,
                           {100, 100},
                           query.width,
                           query.height,
                           0,
                           RendererFlip::NONE,
                           rgba<>{0x00, 0xff, 0x00, 0xff});
    tile->setAnimationFrameStep({0, 0, 64, 64}, 4);
    tile->setAnimationRow(0);
    tile->setTexture(texture);
    tile->setAnimationTime(500);
    tile->startAnimation();
    engine.start(60);
    return 0;
}

int main(int, char **) {
    return launchGame();
}