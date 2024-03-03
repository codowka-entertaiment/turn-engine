#pragma once

namespace TurnEngine::core {
    class Object {
    public:
        Object();
        ~Object();
        virtual void update() = 0;
    };
}