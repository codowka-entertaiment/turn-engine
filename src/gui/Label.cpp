#include "TurnEngine/gui/Label.hpp"

namespace TurnEngine::gui {

    Label::Label(std::string _text, xy<int> _pos, rgba<> _color) {
        text = _text;
        color = _color;
        pos = _pos;
    }

    void Label::draw(render::Drawer* drawer) {
        txr = new Texture(*drawer->getRenderer(), *renderSolid(font, text, color));
        Texture::texture_query query = txr->query();
        // TODO: send drawable and use drawer->draw();
        drawer->getRenderer()->copy({pos.x, pos.y, query.width, query.height}, *txr);
    }
}