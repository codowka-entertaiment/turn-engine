#pragma once

#include "TurnEngine/core/Object2D.hpp"

namespace TurnEngine::core {
    class Area2D: public Object2D {
    private:
        std::vector<Object2D*> objects;
    public:
        Area2D(): Object2D(nullptr, -1000000, false, {0, 0}, 0, 0, nullptr, {0,0,0,0}) {}
        bool contains(Point<int> pos);
        void draw(render::Drawer* drawer) override;
        void addChild(Object2D* obj);
        std::vector<Object2D*> getChildren();
        Object2D* getChild(std::string _name) override;
        void removeChild(Object2D* obj);
        void update(Event* _event) override;
    };
}