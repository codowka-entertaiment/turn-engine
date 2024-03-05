#include "TurnEngine/render/DrawComparator.hpp"

namespace TurnEngine::render {
    bool DrawComparator::operator()(const core::IDrawable& below, const core::IDrawable& above) const {
        return below.depthIndex >= above.depthIndex;
    }
}