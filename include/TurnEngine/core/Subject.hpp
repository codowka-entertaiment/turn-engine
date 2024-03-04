#pragma once

#include <list>

#include "TurnEngine/core/ISubject.hpp"

namespace TurnEngine::core {
    class Subject: public ISubject {
    public:
        ~Subject() override {};

        void attach(IObserver *observer) override;

        void detach(IObserver *observer) override;

        void notify() override;

        void signal(std::string message = "Empty");

    private:
        std::list<IObserver *> list_observer_;
        std::string message_;
    };
}