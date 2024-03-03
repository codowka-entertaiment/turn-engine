#pragma once

#include "Object2D.hpp"

namespace TurnEngine::core {
    class Drawable : Object2D {
    private:
        int depthIndex;
    public:
        Drawable(int _depthIndex): depthIndex(_depthIndex){}
        ~Drawable();
        int getDepthIndex() const;
    };
}