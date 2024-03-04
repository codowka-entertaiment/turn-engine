#pragma once

#include "TurnEngine/core/IObserver.hpp"

namespace TurnEngine::core {
    class ISubject {
    public:
        virtual ~ISubject() = 0;

        virtual void attach(IObserver *observer) = 0;

        virtual void detach(IObserver *observer) = 0;

        virtual void notify() = 0;
    };
}