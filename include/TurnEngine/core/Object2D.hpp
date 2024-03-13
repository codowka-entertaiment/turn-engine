#pragma once

#include "TurnEngine/core/Object.hpp"
#include "TurnEngine/core/IObject2D.hpp"
#include "TurnEngine/render/Drawer.hpp"

namespace TurnEngine::core {
    /// @brief
    /// Class that represents drawable 2D objects
    class Object2D : public IObject2D, public Object {
    public:

        /// @brief
        /// the constructor
        /// @param geo2d::Shape<int> *shape
        /// @param int depthIndex
        /// @param bool isAnimated
        /// @param Point<int> position
        /// @param int width
        /// @param int height
        /// @param Texture *texture
        /// @param Rect<int> rect
        /// @param int angle = 0
        /// @param RendererFlip flip = RendererFlip::NONE
        /// @param rgba<> color = Color::black
        Object2D(
                geo2d::Shape<int> *shape,
                int depthIndex,
                bool isAnimated,
                Point<int> position,
                int width,
                int height,
                Texture *texture,
                Rect<int> rect,
                int angle = 0,
                RendererFlip flip = RendererFlip::NONE,
                rgba<> color = Color::black
        );

        /// @brief
        /// the constructor
        /// @param Object2D* drawable
        Object2D(Object2D *drawable);

        /// @brief
        /// Virtual method which adds Object2D to drawer priority_queue.
        /// Priority is based on depthIndex value
        virtual void draw(render::Drawer *drawer);

        /// @brief
        /// Virtual getter for child Objects2D
        virtual Object2D* getChild(std::string _name);
    };
}