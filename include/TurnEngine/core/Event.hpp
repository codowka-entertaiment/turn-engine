#pragma once

#include "TurnEngine/wrapper/Shapes.hpp"

namespace TurnEngine::core {
    class Event {
    public:
        Point<int> pos;
        std::string msg;
        Event(std::string _msg, Point<int> _pos = {-1, -1});
        void setPosition(Point<int> _pos);
        void setMsg(std::string _msg);
    };
}