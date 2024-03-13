#pragma once

#include <iostream>
#include "TurnEngine/core/Event.hpp"

namespace TurnEngine::core {
    /// @brief
    /// Interface for Observer class
    class IObserver {
    public:
        /// @brief
        /// the destructor
        virtual ~IObserver(){};

        /// @brief
        /// Handle received event
        virtual void update(Event* event) = 0;
    };
}