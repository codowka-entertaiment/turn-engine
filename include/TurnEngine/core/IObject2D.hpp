#pragma once

#include "TurnEngine/wrapper/Shapes.hpp"
#include "TurnEngine/wrapper/Texture.hpp"
#include "TurnEngine/wrapper/Utils.hpp"
#include "TurnEngine/wrapper/Color.hpp"
#include "TurnEngine/geo2d/Shapes.hpp"

namespace TurnEngine::core {
    class IObject2D {
    public:
        geo2d::Shape<int>* shape;
        int depthIndex;
        bool isAnimated;
        Point<int> position;
        int width;
        int height;
        Texture *texture;
        Rect<int> rect;
        int angle;
        RendererFlip flip;
        rgba<> color;

        IObject2D(
                geo2d::Shape<int>* shape,
                int depthIndex,
                bool isAnimated,
                Point<int> position,
                int width,
                int height,
                Texture *texture,
                Rect<int> rect,
                int angle,
                RendererFlip flip,
                rgba<> color
        ) : shape(shape),
            depthIndex(depthIndex),
            isAnimated(isAnimated),
            position(position),
            width(width),
            height(height),
            texture(texture),
            rect(rect),
            angle(angle),
            flip(flip),
            color(color) {}
    };
}