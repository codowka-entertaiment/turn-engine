#pragma once

#include <vector>
#include "TurnEngine/core/Object2D.hpp"
#include "TurnEngine/render/Drawer.hpp"

namespace TurnEngine::core {
    class Scene: public Object2D {
    private:
        std::vector<Object2D*> objects;
        Point<int> pos;
    public:
        Scene(Point<int> pos, int width, int height);
        bool contains(Point<int> pos);
        void draw(render::Drawer* drawer) override;
        void addChild(Object2D* obj);
        void removeChild(Object2D* obj);
    };
}