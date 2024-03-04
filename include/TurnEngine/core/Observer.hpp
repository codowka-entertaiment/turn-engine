#pragma once

#include <vector>

#include "TurnEngine/core/Subject.hpp"
#include "TurnEngine/core/IObserver.hpp"

namespace TurnEngine::core {
    class Observer: public IObserver {
    public:
        Observer();

        ~Observer() {}

        void update(const std::string &message_from_subject) override;

        void unsubscribe(Subject* subject);

        void subscribe(Subject* subject);

        std::string getMessage();

    private:
        std::string message_from_subject_;
        std::vector<Subject*> subjects;
        int number_;
    };
}