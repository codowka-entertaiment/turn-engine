#pragma once

#include <vector>

#include "Observer.hpp"
#include "Object.hpp"
#include "event/Event.hpp"

namespace TurnEngine::core {
    class Subject {
    private:
        std::vector<Observer*> observers; // TODO: Investigate if it the fastest way to notify observers
    public:
        void appendObserver(Observer* observer);
        void removeObserver(Observer* observer);
        void notify(const Object& obj, Event event);
    };
}