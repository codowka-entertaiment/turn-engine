#include "TurnEngine/render/Drawer.hpp"

namespace TurnEngine::render {
    void Drawer::drawLine() {

    }

    void Drawer::drawRect() {

    }

    void Drawer::drawCircle() {

    }

    void Drawer::drawPoints(std::vector<Point<int>> points) {
        std::span<Point<int> const> const span = std::span<Point<int>>(points);
        this->renderer->set_draw_color(Color::green);
        this->renderer->draw_points(span);
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