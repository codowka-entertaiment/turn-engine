#include "TurnEngine/core/Observer.hpp"

namespace TurnEngine::core {
    Observer::Observer(Subject &subject) : subject_(subject) {
            this->subject_.attach(this);
    }

    void Observer::update(const std::string &message_from_subject) {
        message_from_subject_ = message_from_subject;
    }

    void Observer::unsubscribe() {
        subject_.detach(this);
    }
}