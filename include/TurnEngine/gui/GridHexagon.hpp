#pragma once

#include <vector>
#include "TurnEngine/geo2d/Vector.hpp"
#include "TurnEngine/geo2d/Shapes.hpp"
#include "TurnEngine/gui/BaseWidget.hpp"

namespace TurnEngine::gui {
    class GridHexagon {
    private:
        geo2d::PositionInt start_pos;
        int hex_side;
        int rows;
        int cols;
        std::vector<geo2d::HexagonInt*> map;
        gui::BaseWidget* widget;
    public:
        GridHexagon(geo2d::PositionInt _start_pos, int _hex_side, int _rows, int _cols, gui::BaseWidget* _widget);
        void draw(render::Drawer *drawer);
        geo2d::HexagonInt* contains(int x, int y);
    };
}