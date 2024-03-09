#pragma once

#include "TurnEngine/core/Object2D.hpp"
#include "TurnEngine/geo2d/shapes/Shape.hpp"

namespace TurnEngine::gui {
    class Sprite : public core::Object2D, public core::Subject, public core::Observer {
    private:
        bool isPlaying = false;
        int currentFrame = 0;
        int maxFrames;
        int animationRow;
        int animationTime;
        Uint32 currentTick;
        Rect<int> frameStep;
    public:
        Sprite(geo2d::Shape<int> *_shape,
               int _depthIndex,
               bool _isAnimated,
               Point<int> _position,
               int _width,
               int _height,
               int _angle,
               RendererFlip _flip,
               rgba<> _color);

        Sprite(core::Object2D *drawable);

        void startAnimation();

        void stopAnimation();

        void setTexture(Texture *_texture);

        void setAnimationRow(int _row);

        void setAnimationFrameStep(Rect<int> _frameStep, int _maxFrames);

        void setShape(geo2d::Shape<int> *_shape);

        void setAnimationTime(int _milliseconds);

        void draw(render::Drawer *_drawer);
    };
}