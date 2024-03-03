#pragma once

#include "Object.hpp"
#include "event/Event.hpp"

namespace TurnEngine::core {
    class Observer {
    public:
        Observer();
        virtual void onNotify(const Object& obj, Event event) = 0;
    };
}