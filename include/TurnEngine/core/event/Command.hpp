#pragma once

namespace TurnEngine::core {
    class Command {
    public:
        Command() = default;
        virtual void execute() = 0;
    };
}