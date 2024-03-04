#pragma once

#include <queue>
#include <vector>

#include "TurnEngine/core/Observer.hpp"
#include "TurnEngine/core/Drawable.hpp"
#include "TurnEngine/wrapper/Color.hpp"
#include "TurnEngine/wrapper/Renderer.hpp"
#include "TurnEngine/render/DrawComparator.hpp"

namespace TurnEngine::render {
    class Drawer {
    private:
        Renderer* renderer;
        std::priority_queue<core::Drawable, std::vector<core::Drawable>, DrawComparator> drawQueue;
    public:
        explicit Drawer(Renderer* _renderer);
        void draw(const core::Drawable& drawable);
        void renderAll();
        void destroy();
        Renderer* getRenderer();
    };
}