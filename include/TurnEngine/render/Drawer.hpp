#pragma once

#include <queue>
#include <vector>

#include "TurnEngine/core/Observer.hpp"
#include "TurnEngine/core/IObject2D.hpp"
#include "TurnEngine/wrapper/Color.hpp"
#include "TurnEngine/wrapper/Renderer.hpp"
#include "TurnEngine/render/DrawComparator.hpp"

namespace TurnEngine::render {
    /// @brief
    /// Class represents engine drawer
    class Drawer {
    private:
        Renderer *renderer;
        std::priority_queue<core::IObject2D, std::vector<core::IObject2D>, DrawComparator> drawQueue;
    public:
        /// @brief
        /// the constructor
        /// @param Renderer* _renderer
        explicit Drawer(Renderer *_renderer);

        /// @brief
        /// method which puts Object2D into priority_queue
        /// @param const IObject2D &drawable
        void draw(const core::IObject2D &drawable);

        /// @brief
        /// method which pops out and draw all 2D objects from priority_queue
        void renderAll();

        /// @brief
        /// method destroys drawer and hardware renderer
        void destroy();

        /// @brief
        /// getter for renderer
        /// @return Renderer*
        Renderer *getRenderer();
    };
}