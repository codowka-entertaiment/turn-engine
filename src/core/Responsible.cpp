#include "TurnEngine/core/Responsible.hpp"

namespace TurnEngine::core {

    void Responsible::handleRequest() {
        if (successor) successor->handleRequest();
    }

    bool Responsible::doRequest() {
        return numResponsible != -1;
    }

    void Responsible::setResponsible(Responsible *_successor, int _numResponsible) {
        successor = _successor;
        numResponsible = _numResponsible;
    }
}