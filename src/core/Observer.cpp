#include "TurnEngine/core/Observer.hpp"

namespace TurnEngine::core {
    Observer::Observer() {}

    void Observer::update(const std::string &message_from_subject) {
        message_from_subject_ = message_from_subject;
        printf("%s\n", message_from_subject_.c_str());
    }

    void Observer::disconnect(Subject* subject) {
        subject->detach(this);
        subjects.erase(std::remove(subjects.begin(), subjects.end(), subject), subjects.end());
    }

    void Observer::connect(Subject* subject) {
        subjects.push_back(subject);
        subject->attach(this);
    }

    std::string Observer::getMessage() {
        return message_from_subject_;
    }
}