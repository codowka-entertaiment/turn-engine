#pragma once

#include "TurnEngine/core/Responsible.hpp"

namespace TurnEngine::core {
    static uint64_t _counter_ = 0;
    class Object: public Responsible {
    public:
        uint64_t id;
        Object() {
            id = _counter_;
            _counter_++;
        }
        Object(const Object &obj) {
            id = obj.id;
        }
        Object(Object* obj) {
            id = obj->id;
        }
    };
}