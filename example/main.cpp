#include "TurnEngine/Engine.hpp"
#include <vector>

using namespace TurnEngine;
core::Scene* scene;
core::Scene* inner;
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
                printf("Scene contains: %s\n", scene->contains({event.button.x, event.button.y}) ? "true" : "false");
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
    scene->draw(getDrawer());
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
    scene = new core::Scene({0, 0}, engine.getWidth(), engine.getHeight());
    inner = new core::Scene({scene->width / 2, scene->height / 2}, scene->width / 2, scene->height / 2);
    unsigned char r = 0xff;
    unsigned char g = 0x00;
    unsigned char b = 0x00;
    int w = scene->width / 2 / 10;
    int h = scene->height / 2 / 10;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            geo2d::Shape<int> *shape = geo2d::RectangleInt::init_uncheck({j * w, i * h}, w, h);
            auto *tile = new core::Object2D(
                    shape,
                    0,
                    false,
                    {j * w, i * h},
                    w,
                    h,
                    nullptr,
                    {0, 0, 0, 0},
                    0,
                    RendererFlip::NONE,
                    rgba<>{r, g, b, 0xf0});
            scene->addChild(tile);
            if (r == 0xff) {
                r = 0x00;
                g = 0xff;
            }
            else if (g == 0xff) {
                g = 0x00;
                b = 0xff;
            }
            else if (b == 0xff) {
                b = 0x00;
                r = 0xff;
            }
        }
    }
    w = 10;
    h = 10;
    for (int i = 0; i < 10; i++) {
        for (int j =  0; j < 10; j++) {
            geo2d::Shape<int> *shape = geo2d::RectangleInt::init_uncheck({j * w + inner->position.x(), i * h + inner->position.y()}, w, h);
            auto *tile = new core::Object2D(
                    shape,
                    0,
                    false,
                    {j * w + inner->position.x(), i * h + inner->position.y()},
                    w,
                    h,
                    nullptr,
                    {0, 0, 0, 0},
                    0,
                    RendererFlip::NONE,
                    rgba<>{r, g, b, 0xf0});
            inner->addChild(tile);
            if (r == 0xff) {
                r = 0x00;
                g = 0xff;
            }
            else if (g == 0xff) {
                g = 0x00;
                b = 0xff;
            }
            else if (b == 0xff) {
                b = 0x00;
                r = 0xff;
            }
        }
    }
    scene->addChild(inner);
//    auto texture = new Texture(*engine.getRenderer(), "../example/assets/animation.png");
//    auto query = texture->query();
//    tile = new gui::Sprite(0,
//                           true,
//                           {100, 100},
//                           query.width,
//                           query.height,
//                           0,
//                           RendererFlip::NONE,
//                           rgba<>{0x00, 0xff, 0x00, 0xff});
//    tile->setAnimationFrameStep({0, 0, 64, 64}, 4);
//    tile->setAnimationRow(0);
//    tile->setTexture(texture);
//    tile->setAnimationTime(500);
//    tile->startAnimation();
    engine.start(60);
    return 0;
}

int main(int, char **) {
    return launchGame();
}