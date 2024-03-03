#pragma once

#include "Object.hpp"

namespace TurnEngine::core {
    class Responsible {
    private:
        Responsible *successor;
        int numResponsible;
    public:
        constexpr explicit Responsible(Responsible *_successor = nullptr, int _numResponsible = -1) :
                successor(_successor), numResponsible(_numResponsible) {}

        virtual void handleRequest();

        virtual bool doRequest();

        virtual void setResponsible(Responsible* _successor, int _numResponsible);
    };
}