#include "TurnEngine/core/Scene.hpp"

namespace TurnEngine::core {

    bool Scene::contains(Point<int> _pos) {
        if (shape->contains({_pos.x(), _pos.y()})) {
            return true;
        }
        return false;
    }

    void Scene::draw(render::Drawer *drawer) {
        drawer->draw(*this);
        for (auto obj: objects) {
            if (obj->position.x() + obj->width <= position.x() + width &&
                obj->position.x() >= position.x() &&
                obj->position.y() + obj->height <= position.y() + height &&
                obj->position.y() >= position.y())
                obj->draw(drawer);
        }
    }

    void Scene::addChild(Object2D *obj) {
        objects.emplace_back(obj);
    }

    void Scene::removeChild(Object2D *obj) {
        objects.erase(std::remove(objects.begin(), objects.end(), obj), objects.end());
    }

    Scene::Scene(Point<int> pos, int width, int height) : Object2D(
            geo2d::Rectangle<int>::init_uncheck({pos.x(), pos.y()}, width, height),
            -100000,
            false,
            pos,
            width,
            height,
            nullptr,
            {0, 0, 0, 0}
    ) {}

    std::vector<Object2D *> Scene::getChildren() {
        return objects;
    }

    Point<int> Scene::getPosition() {
        return pos;
    }

    Object2D *Scene::getChild(std::string _name) {
        for (auto child: objects) {
            if (child->name == _name) return child;
        }
        return nullptr;
    }
}