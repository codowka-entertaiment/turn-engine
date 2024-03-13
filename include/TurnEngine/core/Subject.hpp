#pragma once

#include <list>

#include "TurnEngine/core/ISubject.hpp"
#include "TurnEngine/core/Event.hpp"

namespace TurnEngine::core {
    /// @brief
    /// Class represents Subject from Observer pattern.
    /// It is sending events to its observers
    class Subject: public ISubject {
    public:
        /// @brief
        /// the destructor
        ~Subject() override {};

        /// @brief
        /// method attaches observer to self
        /// @param IObserver *observer
        void attach(IObserver *observer) override;

        /// @brief
        /// method detaches observer
        /// @param IObserver *observer
        void detach(IObserver *observer) override;

        /// @brief
        /// method notifies all observers about event
        void notify() override;

        /// @brief
        /// method notifies all observers about event
        /// @param Event* _event
        void signal(Event* _event);

    private:
        std::list<IObserver *> list_observer;
        Event* event;
    };
}