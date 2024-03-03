#include "TurnEngine/core/Subject.hpp"

namespace TurnEngine::core {
    void Subject::appendObserver(Observer *observer) {
        observers.push_back(observer);
    }

    void Subject::removeObserver(Observer *observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void Subject::notify(const Object &obj, Event event) {
        for (auto observer : observers) {
            observer->onNotify();
        }
    }
}