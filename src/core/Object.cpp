#include "TurnEngine/core/Object.hpp"

namespace TurnEngine::core {
    Object::Object(std::string _name) {
        id = _counter_;
        _counter_++;
        name = _name;
    }

    Object::Object(const Object &obj) {
        id = obj.id;
        name = obj.name;
    }

    Object::Object(Object* obj) {
        id = obj->id;
        name = obj->name;
    }

    void Object::setName(std::string _name) {
        name = _name;
    }

}