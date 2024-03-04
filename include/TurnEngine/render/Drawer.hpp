#pragma once

#include <queue>
#include <vector>

#include "TurnEngine/core/Observer.hpp"
#include "TurnEngine/core/Object.hpp"
#include "TurnEngine/core/event/Event.hpp"
#include "TurnEngine/core/Drawable.hpp"
#include "TurnEngine/wrapper/Color.hpp"
#include "TurnEngine/wrapper/Renderer.hpp"
#include "TurnEngine/render/DrawComparator.hpp"

namespace TurnEngine::render {
    class Drawer : core::Observer {
    private:
        Renderer* renderer;
        std::priority_queue<core::Drawable, std::vector<core::Drawable>, DrawComparator> drawQueue;
    public:
        explicit Drawer(Renderer* _renderer);
        void draw(const core::Drawable& drawable);
        void renderAll();
        void destroy();
        Renderer* getRenderer();
        void onNotify(const core::Object& obj, core::Event event) final{ };
    };
}