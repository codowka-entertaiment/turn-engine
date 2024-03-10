#include "TurnEngine/core/Event.hpp"

namespace TurnEngine::core {
    Event::Event(std::string _msg, Point<int> _pos) {
        msg = _msg;
        pos = _pos;
    }

    void Event::setPosition(Point<int> _pos) {
        pos = _pos;
    }

    void Event::setMsg(std::string _msg) {
        msg = _msg;
    }
}