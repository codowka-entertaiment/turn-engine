#include "TurnEngine/core/Scene.hpp"

namespace TurnEngine::core {

    bool Scene::contains(Point<int> _pos) {
        if (shape->contains({_pos.x(), _pos.y()})) {
            return true;
        }
        return false;
    }

    void Scene::draw(render::Drawer *drawer) {
        drawer->getRenderer()->set_clip_rect({position.x(), position.y(), width, height});
        drawer->draw(*this);
        drawer->renderAll();
        for (auto obj: objects) {
            obj->draw(drawer);
        }
        drawer->renderAll();
    }

    void Scene::addChild(Object2D *obj) {
        attach(obj);
        objects.emplace_back(obj);
    }

    void Scene::removeChild(Object2D *obj) {
        detach(obj);
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
            if (child->getName() == _name) return child;
        }
        return nullptr;
    }

    void Scene::update(Event *_event) {
        for (auto obj : objects) {
            if (!(_event->pos.x() - obj->position.x() > obj->width ||
                _event->pos.y() - obj->position.y() > obj->height) ||
                (_event->pos.x() == -1 && _event->pos.y() == -1))
            obj->update(_event);
        }
    }
}