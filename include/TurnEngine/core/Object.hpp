#pragma once

#include "Observer.hpp"

namespace TurnEngine::core {
    class Object: Observer {
    public:
        Object();
        ~Object();
        virtual void update() = 0;
    };
}