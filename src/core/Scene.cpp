#include "TurnEngine/core/Scene.hpp"

namespace TurnEngine::core {

    bool Scene::contains(Point<int> _pos) {
        if (shape->contains({_pos.x(), _pos.y()})) {
            return true;
        }
        return false;
    }

    void Scene::draw(render::Drawer *drawer) {
        for (auto obj: objects) {
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
}