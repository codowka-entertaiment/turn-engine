#include "TurnEngine/render/Drawer.hpp"

namespace TurnEngine::render {
    void Drawer::drawLine() {

    }

    void Drawer::drawRect() {

    }

    void Drawer::drawCircle() {

    }

    void Drawer::drawPoints(std::vector<Point<int>> points, rgba<> color) {
        this->renderer->set_draw_color(color);
        for (int i = 0; i < points.size(); i++) {
            this->renderer->draw_point(points[i]);
        }
    }

    void Drawer::renderAll() {

    }

    Drawer::Drawer(Renderer* _renderer) {
        this->renderer = _renderer;
    }

    Renderer* Drawer::getRenderer() {
        return this->renderer;
    }

    void Drawer::destroy() {
        this->renderer->destroy();
    }
}