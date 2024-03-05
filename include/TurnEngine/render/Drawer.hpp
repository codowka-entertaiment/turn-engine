#pragma once

#include <queue>
#include <vector>

#include "TurnEngine/core/Observer.hpp"
#include "TurnEngine/core/IDrawable.hpp"
#include "TurnEngine/wrapper/Color.hpp"
#include "TurnEngine/wrapper/Renderer.hpp"
#include "TurnEngine/render/DrawComparator.hpp"

namespace TurnEngine::render {
    class Drawer {
    private:
        Renderer* renderer;
        std::priority_queue<core::IDrawable, std::vector<core::IDrawable>, DrawComparator> drawQueue;
    public:
        explicit Drawer(Renderer* _renderer);
        void draw(const core::IDrawable& drawable);
        void renderAll();
        void destroy();
        Renderer* getRenderer();
    };
}