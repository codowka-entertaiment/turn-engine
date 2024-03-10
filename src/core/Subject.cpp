#include <utility>

#include "TurnEngine/core/Subject.hpp"

namespace TurnEngine::core {
    void Subject::attach(IObserver *observer) {
        list_observer.push_back(observer);
    }

    void Subject::detach(IObserver *observer) {
        list_observer.remove(observer);
    }

    void Subject::notify() {
        auto iterator = list_observer.begin();
        while (iterator != list_observer.end()) {
            (*iterator)->update(event);
            ++iterator;
        }
    }

    void Subject::signal(Event* _event) {
        this->event = _event;
        notify();
    }
}