#include "TurnEngine/gui/Sprite.hpp"

namespace TurnEngine::gui {

    Sprite::Sprite(
            int _depthIndex,
            bool _isAnimated,
            Point<int> _position,
            int _width,
            int _height,
            int _angle,
            RendererFlip _flip,
            rgba<> _color
    ) :
            core::Object2D(
                    _depthIndex, _isAnimated, _position, _width, _height, nullptr, {0, 0, 0, 0}, _angle, _flip, _color
            ) {}

    Sprite::Sprite(core::Object2D *drawable) :
            core::Object2D(drawable) {}

    void Sprite::startAnimation() {
        this->isPlaying = true;
    }

    void Sprite::stopAnimation() {
        this->isPlaying = false;
    }

    void Sprite::draw(render::Drawer* _drawer) {
        if (isAnimated) {
            if (SDL_GetTicks() - currentTick >= animationTime / maxFrames) {
                if (isPlaying) currentFrame += 1;
                if (currentFrame >= maxFrames) currentFrame = 0;
                rect.x() = currentFrame * rect.w();
                rect.y() = animationRow * rect.h();
                currentTick = SDL_GetTicks();
            }
        }
        _drawer->draw(*this);
    }

    void Sprite::setTexture(Texture *_texture) {
        texture = _texture;
    }

    void Sprite::setAnimationRow(int _row) {
        animationRow = _row;
    }

    void Sprite::setAnimationFrameStep(Rect<int> _frameStep, int _maxFrames) {
        frameStep = _frameStep;
        maxFrames = _maxFrames;
        rect = frameStep;
    }

    void Sprite::setShape(geo2d::Shape<int> *_shape) {
        shape = _shape;
    }

    void Sprite::setAnimationTime(int _milliseconds) {
        animationTime = _milliseconds;
    }

}