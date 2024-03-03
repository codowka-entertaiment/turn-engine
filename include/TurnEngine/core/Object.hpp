#pragma once

namespace TurnEngine::core {
    class Object {
    public:
        Object() = default;
        ~Object();
        virtual void update() = 0;
    };
}