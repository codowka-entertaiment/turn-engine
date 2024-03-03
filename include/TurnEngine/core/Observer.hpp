#pragma once

namespace TurnEngine::core {
    class Observer {
    public:
        virtual ~Observer();
        virtual void onNotify() = 0; // TODO: Params must be: const Entity& entity, Event event
    };
}