#pragma once

#include <list>

#include "TurnEngine/core/ISubject.hpp"
#include "TurnEngine/core/Event.hpp"

namespace TurnEngine::core {
    class Subject: public ISubject {
    public:
        ~Subject() override {};

        void attach(IObserver *observer) override;

        void detach(IObserver *observer) override;

        void notify() override;

        void signal(Event* _event);

    private:
        std::list<IObserver *> list_observer;
        Event* event;
    };
}