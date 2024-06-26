#pragma once

#include <vector>

#include "TurnEngine/core/Subject.hpp"
#include "TurnEngine/core/IObserver.hpp"

namespace TurnEngine::core {
    /// @brief
    /// That class implements Observer pattern.
    /// No params should be defined
    class Observer: public IObserver {
    public:
        Observer();

        ~Observer() {}

        /// @brief
        /// That func is used by Subject, don't call it explicitly.
        /// Derived classes must override that method to use it with game logic
        void update(Event* _event) override;

        /// @brief
        /// That func detaches Observer class from Subject
        void disconnect(Subject* subject);

        /// @brief
        /// That func attaches Observer class to Subject
        void connect(Subject* subject);

        /// @brief
        /// Getter for current event
        Event* getEvent();

    protected:
        Event* event;
        std::vector<Subject*> subjects;
    };
}