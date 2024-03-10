#pragma once

#include <iostream>
#include "TurnEngine/core/Event.hpp"

namespace TurnEngine::core {
    class IObserver {
    public:
        virtual ~IObserver(){};
        virtual void update(Event* event) = 0;
    };
}