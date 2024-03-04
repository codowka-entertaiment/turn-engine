#pragma once

#include <iostream>

namespace TurnEngine::core {
    class IObserver {
    public:
        virtual ~IObserver(){};
        virtual void update(const std::string &message_from_subject) = 0;
    };
}