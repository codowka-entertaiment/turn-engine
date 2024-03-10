#pragma once

#include "TurnEngine/core/Responsible.hpp"
#include "TurnEngine/core/Observer.hpp"
#include "TurnEngine/core/Subject.hpp"

namespace TurnEngine::core {
    static uint64_t _counter_ = 0;

    class Object : public Observer, public Subject {
    public:
        std::string name;
        uint64_t id;

        Object(std::string _name);

        Object(const Object &obj);

        Object(Object *obj);

        void setName(std::string _name);
    };
}