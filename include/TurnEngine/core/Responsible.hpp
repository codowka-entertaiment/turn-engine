#pragma once

#include <iostream>

#include "Object.hpp"

namespace TurnEngine::core {
    class Responsible {
    private:
        Responsible *successor;
        std::string responsible;
    public:
        constexpr explicit Responsible(Responsible *_successor = nullptr, std::string _responsible = "_") :
                successor(_successor), responsible(_responsible) {}

        virtual void handleRequest();

        virtual bool doRequest();

        virtual void setResponsible(Responsible* _successor, std::string _responsible);
    };
}