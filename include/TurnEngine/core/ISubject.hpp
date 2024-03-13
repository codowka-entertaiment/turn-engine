#pragma once

#include "TurnEngine/core/IObserver.hpp"

namespace TurnEngine::core {
    /// @brief
    /// Interface for Subject class
    class ISubject {
    public:
        /// @brief
        /// the destructor
        virtual ~ISubject() {};

        /// @brief
        /// Attaches observer to send it events
        virtual void attach(IObserver *observer) = 0;

        /// @brief
        /// Detaches observer. It won't be able to receive events from subject
        virtual void detach(IObserver *observer) = 0;

        /// @brief
        /// Send event to each observer
        virtual void notify() = 0;
    };
}