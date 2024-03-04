#pragma once

#include "TurnEngine/core/Subject.hpp"
#include "TurnEngine/core/IObserver.hpp"

namespace TurnEngine::core {
    class Observer: public IObserver {
    public:
        Observer(Subject &subject);

        ~Observer() {}

        void update(const std::string &message_from_subject) override;

        void unsubscribe();

    private:
        std::string message_from_subject_;
        Subject &subject_;
        int number_;
    };
}