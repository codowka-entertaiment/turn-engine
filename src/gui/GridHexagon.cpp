#include "TurnEngine/gui/GridHexagon.hpp"

namespace TurnEngine::gui {

    GridHexagon::GridHexagon(geo2d::PositionInt _start_pos, int _hex_side, int _rows, int _cols,
                             gui::BaseWidget *_widget) :
            start_pos(_start_pos), hex_side(_hex_side), rows(_rows), cols(_cols) {
        widget = _widget;
        int sprite_height = (int) (hex_side * sqrt(3));
        int m = 1;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                // TODO: Generate map
                geo2d::PositionInt pos{start_pos.x + j * sprite_height + (m + 1) * sprite_height / 4,
                                       start_pos.y + i * sprite_height - i * sprite_height / 5};
                map.push_back(geo2d::HexagonInt::init_uncheck(pos, hex_side));
            }
            m *= -1;
        }
    }

    void GridHexagon::draw(render::Drawer *drawer) {
        this->widget->draw(drawer);
        int sprite_height = (int) (hex_side * sqrt(3));
        auto texture1 = new Texture(*drawer->getRenderer(), "../example/assets/hexagon_blue1.png");
        texture1->set_color_mod({0x00, 0x00, 0x00});
        texture1->set_alpha_mod(80);
        int m = 1;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                core::Drawable(
                        1,
                        false,
                        {start_pos.x + j * sprite_height + (m + 1) * sprite_height / 4,
                         start_pos.y + i * sprite_height - i * sprite_height / 5},
                        sprite_height,
                        sprite_height,
                        texture1,
                        {0, 0, 0, 0},
                        90,
                        RendererFlip::NONE,
                        Color::red
                ).draw(drawer);
            }
            m *= -1;
        }
    }

    geo2d::HexagonInt *GridHexagon::contains(int x, int y) {
        int grid_x = x - start_pos.x;
        int grid_y = y - start_pos.y;

    }
}