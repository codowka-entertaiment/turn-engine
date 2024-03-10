#include "TurnEngine/Engine.hpp"
#include <vector>

using namespace TurnEngine;
core::Scene *scene;
core::Scene *inner;
core::Subject* eventSender;

class Tile : public gui::Sprite {
public:
    Tile(
            geo2d::Shape<int> *_shape,
            int _depthIndex,
            bool _isAnimated,
            Point<int> _position,
            int _width,
            int _height,
            int _angle,
            RendererFlip _flip,
            rgba<> _color
    ) : gui::Sprite(
            _shape,
            _depthIndex,
            _isAnimated,
            _position,
            _width,
            _height,
            _angle,
            _flip,
            _color
    ) {}
    void update(core::Event* event) override {
        if (event->msg == "click" && shape->contains({event->pos.x(), event->pos.y()})) {
            color = rgba<>{0xff, 0xff, 0xff, 0xff};
            printf("I am clicked man!\n");
        }
        if (event->msg == "moveUp") {
            position.y() -= 2;
        } else if (event->msg == "moveDown") {
            position.y() += 2;
        } else if (event->msg == "moveLeft") {
            position.x() -= 2;
        } else if (event->msg == "moveRight") {
            position.x() += 2;
        }
    }
};

// Define that method to handle events
void Engine::onPollEvents() {
    int last_x = 0, last_y = 0;
    SDL_GetMouseState(&last_x, &last_y);
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
            last_x = event.motion.x;
            last_y = event.motion.y;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            // Handle mouse button click
            if (event.button.button == SDL_BUTTON_LEFT) {
                printf("LMB DOWN: x:%d y:%d\n", event.button.x, event.button.y);
                printf("Scene contains: %s\n", scene->contains({event.button.x, event.button.y}) ? "true" : "false");
            }
            if (event.button.button == SDL_BUTTON_RIGHT) {
                printf("RMB DOWN: x:%d y:%d\n", event.button.x, event.button.y);
            }
            eventSender->signal(new core::Event("click", {event.button.x, event.button.y}));
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
    if (last_y <= 5) {
        eventSender->signal(new core::Event("moveUp"));
    }
    if (last_y >= height - 5) {
        eventSender->signal(new core::Event("moveDown"));
    }
    if (last_x <= 5) {
        eventSender->signal(new core::Event("moveLeft"));
    }
    if (last_x >= width - 5) {
        eventSender->signal(new core::Event("moveRight"));
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
    if (!engine.createWindow("Testing", WindowFlags::FULLSCREEN_DESKTOP)) {
        return EXIT_FAILURE;
    }
    if (!engine.createDrawer(RendererFlags::ACCELERATED | RendererFlags::PRESENTVSYNC)) {
        return EXIT_FAILURE;
    }
    // Custom cursor
    auto cursor = new Cursor("../example/assets/cursor.png");
    cursor->enable();
    scene = new core::Scene({0, 0}, engine.getWidth(), engine.getHeight());
    scene->texture = new Texture(*engine.getRenderer(), "../example/assets/background.jpeg");
    inner = new core::Scene({50, 50}, scene->width / 10 * 8, scene->height / 10 * 8);
    inner->color = {0x00, 0x00, 0x00, 0x00};
    inner->depthIndex = scene->depthIndex - 1;
    eventSender = new core::Subject();
    unsigned char r = 0x00;
    unsigned char g = 0x00;
    unsigned char b = 0x00;
    int w = 20;
    int h = 20;
    auto border = new gui::Sprite(
            geo2d::RectangleInt::init_uncheck(
                    {inner->position.x(), inner->position.y()}, w, h),
            10000,
            false,
            {inner->position.x(), inner->position.y()},
            inner->width,
            inner->height,
            0,
            RendererFlip::NONE,
            rgba<>{0xff, g, b, 0xf0});
    border->setTexture(new Texture(*engine.getRenderer(), "../example/assets/border_dead.png"));
    border->name = "border";
    inner->addChild(border);
    for (int i = 0; i < 101; i++) {
        for (int j = 0; j < 101; j++) {
            geo2d::Shape<int> *shape = geo2d::RectangleInt::init_uncheck(
                    {j * w, i * h}, w, h);
            auto *tile = new Tile(
                    shape,
                    -1,
                    false,
                    {j * w, i * h},
                    w,
                    h,
                    0,
                    RendererFlip::NONE,
                    rgba<>{r, g, b, 0xf0});
            tile->setName(std::format("tile%d", tile->id));
            tile->connect(eventSender);
            inner->addChild(tile);
            if (b == 0xff) {
                b = 0x00;
                g = 0xff;
            } else {
                b = 0xff;
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