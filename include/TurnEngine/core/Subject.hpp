#pragma once

#include "Observer.hpp"
#include "queue"

namespace TurnEngine::core {
    class Subject {
    private:
        std::queue<Observer*> observers;
    public:
        void appendObserver(Observer* observer);
        void removeObserver(Observer* observer);
        void notify(); // TODO: Parameters must be const Entity& entity, Event event. Add implementation
    };
}