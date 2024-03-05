#include "TurnEngine/render/Drawer.hpp"

namespace TurnEngine::render {

    /// @brief
    /// That function puts Drawable inside queue
    void Drawer::draw(const core::IDrawable &drawable) {
        this->drawQueue.push(drawable);
    }

    /// @brief
    /// That function pops all loaded Drawables in queue and renders it to the window
    void Drawer::renderAll() {
        while (!this->drawQueue.empty()) {
            core::IDrawable drawable = this->drawQueue.top();
            if (drawable.texture == nullptr) {
                getRenderer()->set_draw_color(drawable.color);
                Rect<int> rect = {drawable.position.x(), drawable.position.y(), drawable.width, drawable.height};
                getRenderer()->fill_rect(rect);
                this->drawQueue.pop();
                continue;
            }
            if (drawable.isAnimated) {
                getRenderer()->copy_ex(
                        Rect<int>{
                                drawable.position.x(),
                                drawable.position.y(),
                                drawable.width,
                                drawable.height
                        },
                        *drawable.texture,
                        drawable.rect,
                        drawable.angle,
                        drawable.position,
                        drawable.flip);
            } else {
                getRenderer()->copy_ex(
                        Rect<int>{
                                drawable.position.x(),
                                drawable.position.y(),
                                drawable.width,
                                drawable.height
                        },
                        *drawable.texture,
                        drawable.angle,
                        drawable.flip);
            }
            this->drawQueue.pop();
        }
    }

    Drawer::Drawer(Renderer *_renderer) {
        this->renderer = _renderer;
    }

    Renderer *Drawer::getRenderer() {
        return this->renderer;
    }

    void Drawer::destroy() {
        this->renderer->destroy();
    }
}