#pragma once

#include "TurnEngine/core/Observer.hpp"
#include "TurnEngine/core/Subject.hpp"

namespace TurnEngine::core {
    static uint64_t _counter_ = 0;

    /// @brief
    /// Base class Object. It must be base class for all game objects
    class Object : public Observer, public Subject {
    public:
        std::string name;
        uint64_t id;

        /// @brief
        /// the constructor
        /// @param std::string _name
        Object(std::string _name);

        Object(const Object &obj);

        Object(Object *obj);

        /// @brief
        /// Object name setter
        /// @param std::string _name
        void setName(std::string _name);
    };
}