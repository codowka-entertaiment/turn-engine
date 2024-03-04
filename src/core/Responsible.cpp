#include "TurnEngine/core/Responsible.hpp"

namespace TurnEngine::core {

    void Responsible::handleRequest() {
        if (successor) successor->handleRequest();
    }

    bool Responsible::doRequest() {
        return responsible != "_";
    }

    void Responsible::setResponsible(Responsible *_successor, std::string _responsible) {
        successor = _successor;
        responsible = _responsible;
    }
}