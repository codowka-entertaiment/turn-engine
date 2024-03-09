#include "TurnEngine/gui/Label.hpp"

namespace TurnEngine::gui {

    void Label::draw(render::Drawer *drawer) {
        auto s = renderBlended(font, text, color);
        if (s->surface_ == nullptr) {
            printf("aaaaa\n");
        }
        auto txr = new Texture(*drawer->getRenderer(), *renderBlended(font, text, color));
        Texture::texture_query query = txr->query();
        height = query.height;
        width = query.width;
        texture = txr;
        drawer->draw(*this);
    }

    Label::Label(
            Font* _font,
            std::string _text,
            xy<int> _pos,
            rgba<> _color,
            int _depthIndex,
            int _angle,
            RendererFlip _flip
    ): core::Object2D({_depthIndex, false, {_pos.x, _pos.y}, 0, 0, nullptr, {0, 0, 0, 0}, _angle, _flip, _color}) {
        font = _font;
        text = _text;
        color = _color;
        pos = _pos;
    }
}