#include "TurnEngine/core/Scene.hpp"

namespace TurnEngine::core {

    bool Scene::contains(Point<int> _pos) {
        if (shape->contains({_pos.x(), _pos.y()})) {
            printf("Inside scene! ID: %llu\n", id);
        }
        for (const auto &obj: objects) {
            if (obj->shape->contains({_pos.x(), _pos.y()})) {
                return true;
            }
        }
        return false;
    }

    void Scene::draw(render::Drawer *drawer) {
        printf("Drawing %llu\n", id);
        for (auto obj: objects) {
            obj->draw(drawer);
        }
    }

    void Scene::addChild(Object2D *obj) {
        objects.emplace_back(obj);
    }

    void Scene::removeChild(Object2D *obj) {

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
    ) {
        printf("MINE ID: %llu\n", id);
    }
}