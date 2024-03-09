#pragma once

#include <queue>
#include <vector>

#include "TurnEngine/core/Observer.hpp"
#include "TurnEngine/core/IObject2D.hpp"
#include "TurnEngine/wrapper/Color.hpp"
#include "TurnEngine/wrapper/Renderer.hpp"
#include "TurnEngine/render/DrawComparator.hpp"

namespace TurnEngine::render {
    class Drawer {
    private:
        Renderer* renderer;
        std::priority_queue<core::IObject2D, std::vector<core::IObject2D>, DrawComparator> drawQueue;
    public:
        explicit Drawer(Renderer* _renderer);
        void draw(const core::IObject2D& drawable);
        void renderAll();
        void destroy();
        Renderer* getRenderer();
    };
}