#pragma once

#include "TurnEngine/core/Object2D.hpp"
#include "TurnEngine/geo2d/shapes/Shape.hpp"

namespace TurnEngine::gui {
    /// @brief
    /// Class which represents sprites
    class Sprite : public core::Object2D {
    private:
        bool isPlaying = false;
        int currentFrame = 0;
        int maxFrames;
        int animationRow;
        int animationTime;
        Uint32 currentTick;
        Rect<int> frameStep;
    public:
        /// @brief
        /// the constructor
        /// @param geo2d::Shape<int> *_shape
        /// @param int _depthIndex
        /// @param bool _isAnimated
        /// @param Point<int> _position
        /// @param int _width
        /// @param int _height
        /// @param int _angle
        /// @param RendererFlip _flip
        /// @param rgba<> _color
        Sprite(geo2d::Shape<int> *_shape,
               int _depthIndex,
               bool _isAnimated,
               Point<int> _position,
               int _width,
               int _height,
               int _angle,
               RendererFlip _flip,
               rgba<> _color);

        /// @brief
        /// the constructor
        /// @param Object2D *drawable
        Sprite(core::Object2D *drawable);

        /// @brief
        /// method starts sprite animation
        void startAnimation();

        /// @brief
        /// method stops sprite animation
        void stopAnimation();

        /// @brief
        /// method sets texture to sprite
        /// @param Texture _texture
        void setTexture(Texture *_texture);

        /// @brief
        /// method sets row in spritesheet
        /// @param int _row
        void setAnimationRow(int _row);


        /// @brief
        /// method sets size of texture and max frames in spritesheet
        /// @param Rect<int> _frameStep
        /// @param int _maxFrames
        void setAnimationFrameStep(Rect<int> _frameStep, int _maxFrames);

        /// @brief
        /// method sets shape to sprite
        /// @param Shape<int> *_shape
        void setShape(geo2d::Shape<int> *_shape);

        /// @brief
        /// method sets animation time in milliseconds
        /// @param int _milliseconds
        void setAnimationTime(int _milliseconds);

        /// @brief
        /// method draws sprite
        /// @param Drawer *_drawer
        void draw(render::Drawer *_drawer);
    };
}