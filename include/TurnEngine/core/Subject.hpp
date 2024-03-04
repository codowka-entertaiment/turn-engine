#pragma once

#include <list>

#include "TurnEngine/core/ISubject.hpp"

namespace TurnEngine::core {
    class Subject: public ISubject {
    public:
        ~Subject() override = 0;

        void attach(IObserver *observer) override;

        void detach(IObserver *observer) override;

        void notify() override;

        void createMessage(std::string message = "Empty");

        void signal();

    private:
        std::list<IObserver *> list_observer_;
        std::string message_;
    };
}