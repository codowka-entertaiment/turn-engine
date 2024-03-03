#include "TurnEngine/render/Drawer.hpp"

namespace TurnEngine::render {
    void Drawer::drawLine() {

    }

    void Drawer::drawRect() {

    }

    void Drawer::drawCircle() {

    }

    void Drawer::drawPoints() {

    }

    void Drawer::renderAll() {

    }

    Drawer::Drawer(Renderer* _renderer) {
        this->renderer = _renderer;
    }

    Renderer* Drawer::getRenderer() {
        return this->renderer;
    }
}