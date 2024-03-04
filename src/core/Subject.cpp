#include <utility>

#include "TurnEngine/core/Subject.hpp"

namespace TurnEngine::core {
    void Subject::attach(IObserver *observer) {
        list_observer_.push_back(observer);
    }

    void Subject::detach(IObserver *observer) {
        list_observer_.remove(observer);
    }

    void Subject::notify() {
        auto iterator = list_observer_.begin();
        while (iterator != list_observer_.end()) {
            (*iterator)->update(message_);
            ++iterator;
        }
    }

    void Subject::createMessage(std::string message) {
        this->message_ = std::move(message);
        notify();
    }

    void Subject::signal() {
        notify();
    }
}