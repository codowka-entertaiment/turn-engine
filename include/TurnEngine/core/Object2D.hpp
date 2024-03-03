#pragma once

#include "Object.hpp"

namespace TurnEngine::core {
    class Object2D : Object {
    public:
        Object2D() = default;
        ~Object2D();
        virtual void draw() = 0;
        virtual void clean() = 0;
    };
}