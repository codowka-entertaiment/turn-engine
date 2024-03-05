#include "TurnEngine/Engine.hpp"
#include "TurnEngine/gui/BaseWidget.hpp"

using namespace TurnEngine;

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

// Define that method to implement game logic, which updates state of your game
void Engine::onUpdate() {

}

// Define that method to implement drawer logic (IDK somebody try to use it with threads)
void Engine::onDraw() {
    Uint32 start = SDL_GetTicks();
    if (start - currentTicks > 1000 / fps) {
        currentTicks = start;
    }
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
    Button* startButton = new Button();
    Button* exitButton = new Button();

    // Create observers
    Player *player = new Player();
    Enemy *enemy1 = new Enemy();
    Enemy *enemy2 = new Enemy();

    // Observers subscribing subject
    player->subscribe(startButton);
    enemy1->subscribe(startButton);
    enemy2->subscribe(startButton);
    player->subscribe(exitButton);
    enemy1->subscribe(exitButton);
    enemy2->subscribe(exitButton);

    // Observers unsubscribing subject
    enemy1->unsubscribe(exitButton);
    enemy2->unsubscribe(exitButton);

    // Subjects send signal
    startButton->signal("start_game");
    exitButton->signal("exit_game");
}

int main(int, char **) {
    testObserverPattern();
    //return launchGame();
}