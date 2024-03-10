#include "TurnEngine/core/Observer.hpp"

namespace TurnEngine::core {
    Observer::Observer() {}

    void Observer::update(Event* _event) {
        event = _event;
    }

    void Observer::disconnect(Subject* subject) {
        subject->detach(this);
        subjects.erase(std::remove(subjects.begin(), subjects.end(), subject), subjects.end());
    }

    void Observer::connect(Subject* subject) {
        subjects.push_back(subject);
        subject->attach(this);
    }

    Event* Observer::getEvent() {
        return event;
    }
}