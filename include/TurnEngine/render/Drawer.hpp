#pragma once

#include <queue>

#include "TurnEngine/core/Observer.hpp"
#include "TurnEngine/wrapper/Renderer.hpp"
#include "TurnEngine/core/Object.hpp"
#include "TurnEngine/core/event/Event.hpp"
#include "DrawComparator.hpp"

namespace TurnEngine::render {
    class Drawer : core::Observer {
    private:
        Renderer* renderer;
        std::priority_queue<int, std::queue<int>, DrawComparator> drawQueue;
    public:
        explicit Drawer(Renderer* _renderer);
        static void drawLine();
        static void drawRect();
        static void drawCircle();
        static void drawPoints();
        static void renderAll();
        Renderer* getRenderer();
        void onNotify(const core::Object& obj, core::Event event) final{ };
    };
}