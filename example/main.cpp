#include "TurnEngine/Engine.hpp"
#include <vector>

using namespace TurnEngine;
std::vector<gui::BaseWidget *> map;
Texture *texture1, *texture2;
gui::BaseWidget* widget;

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
                geo2d::PositionInt pos{event.motion.x, event.motion.y};
                for (int i = 0; i < map.size(); i++) {
                    if (map[i]->shape->contains(pos)) {
                        map[i]->texture = texture2;
                    }
                }
            }
            if (event.button.button == SDL_BUTTON_RIGHT) {
                printf("RMB DOWN: x:%d y:%d\n", event.button.x, event.motion.y);
                geo2d::PositionInt pos{event.motion.x, event.motion.y};
                for (int i = 0; i < map.size(); i++) {
                    if (map[i]->shape->contains(pos)) {
                        map[i]->texture = texture1;
                    }
                }
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
    for (auto tile: map) {
        // Possible two ways to draw Drawable object
        // 1. Call draw from Drawable object
        tile->draw(getDrawer());
        widget->draw(getDrawer());
        // 2. Call draw from Drawer object
        // getDrawer()->draw(*tile);
    }
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
    int c1 = 50;
    engine.getRenderer()->set_draw_blend_mode(BlendMode::BLEND);
    widget = new gui::BaseWidget(0,
                                 {0, 0},
                                 c1 / 2 + c1 * 18,
                                 c1 / 2 + c1 * 14 - 14 * c1 / 5,
                                 new Texture(*engine.getRenderer(), "../example/assets/grass.jpeg"),
                                 geo2d::RectangleInt::init_uncheck({20, 20}, 20, 20),
                                 0,
                                 RendererFlip::NONE,
                                 rgba<>{0x00, 0xff, 0x00, 0xff});
    texture1 = new Texture(*engine.getRenderer(), "../example/assets/hexagon_blue.png");
    texture1->set_alpha_mod(90);
    texture1->set_color_mod({0x00, 0x00, 0x00});
    texture2 = new Texture(*engine.getRenderer(), "../example/assets/hexagon_orange.png");
    texture2->set_alpha_mod(70);
    texture2->set_color_mod({0x00, 0x50, 0x00});
    int m = 1;
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 18; j++) {
            geo2d::PositionInt pos{j * c1 + (m + 1) * c1 / 4 + 25, i * c1 - i * c1 / 5 + c1 / 2};
            Point point{j * c1 + (m + 1) * c1 / 4, i * c1 - i * c1 / 5};
            map.push_back(new gui::BaseWidget(
                                  1, // depthIndex
                                  point, // Position
                                  c1,
                                  c1,
                                  texture1,
                                  geo2d::HexagonInt::init_uncheck(pos, (int)(c1 / 2.5)),
                                  90,
                                  RendererFlip::NONE,
                                  Color::red
                          )
            );
        }
        m *= -1;
    }
    engine.start(60);
    return 0;
}

// Observable class must be inherited by core::Subject (No methods needed to be overridden)
class Button : public core::Subject {
};

// Observer class must be inherited by core::Observer (Override method update to use it with your game logic)
class Player : public core::Observer {
    void update(const std::string &message_from_subject) override {
        message_from_subject_ = message_from_subject;
        printf("Player: Subject notified about %s\n", message_from_subject.c_str());
    }
};

// Observer class must be inherited by core::Observer (Override method update to use it with your game logic)
class Enemy : public core::Observer {
    void update(const std::string &message_from_subject) override {
        message_from_subject_ = message_from_subject;
        printf("Enemy: Subject notified about %s\n", message_from_subject.c_str());
    }
};

// Observer pattern usage example
void testObserverPattern() {

    // Create subjects
    Button *startButton = new Button();
    Button *exitButton = new Button();

    // Create observers
    Player *player = new Player();
    Enemy *enemy1 = new Enemy();
    Enemy *enemy2 = new Enemy();

    // Observers subscribing subject
    player->connect(startButton);
    enemy1->connect(startButton);
    enemy2->connect(startButton);
    player->connect(exitButton);
    enemy1->connect(exitButton);
    enemy2->connect(exitButton);

    // Observers unsubscribing subject
    enemy1->disconnect(exitButton);
    enemy2->disconnect(exitButton);

    // Subjects send signal
    startButton->signal("start_game");
    exitButton->signal("exit_game");
}

int main(int, char **) {
    //testObserverPattern();
    return launchGame();
}