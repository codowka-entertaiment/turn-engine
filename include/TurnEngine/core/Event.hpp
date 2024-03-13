#pragma once

#include "TurnEngine/wrapper/Shapes.hpp"

namespace TurnEngine::core {
    /// @brief
    /// Class stands for describing game events, such as click, motion, etc.
    class Event {
    public:
        Point<int> pos;
        std::string msg;

        /// @brief
        /// @param std::string _msg
        /// @param Point<int> _pos
        Event(std::string _msg, Point<int> _pos = {-1, -1});

        /// @brief
        /// That method sets event position
        void setPosition(Point<int> _pos);

        /// @brief
        /// That method sets event message
        void setMsg(std::string _msg);
    };
}