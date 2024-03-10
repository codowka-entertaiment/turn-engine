#include "TurnEngine/core/Area2D.hpp"

namespace TurnEngine::core {

    bool Area2D::contains(Point<int> pos) {
        for (auto obj : objects) {
            if (obj->shape->contains({pos.x(), pos.y()})) {
                return true;
            }
        }
        return false;
    }

    void Area2D::draw(render::Drawer *drawer) {
        for (auto obj : objects) {
            obj->draw(drawer);
        }
    }

    void Area2D::addChild(Object2D *obj) {
        attach(obj);
        objects.emplace_back(obj);
    }

    std::vector<Object2D *> Area2D::getChildren() {
        return objects;
    }

    Object2D *Area2D::getChild(std::string _name) {
        for (auto child: objects) {
            if (child->name == _name) return child;
        }
        return nullptr;
    }

    void Area2D::removeChild(Object2D *obj) {
        detach(obj);
        objects.erase(std::remove(objects.begin(), objects.end(), obj), objects.end());
    }

    void Area2D::update(Event *_event) {
        for (auto obj : objects) {
            obj->update(_event);
        }
    }
}