#include "TurnEngine/render/DrawComparator.hpp"

namespace TurnEngine::render {
    bool DrawComparator::operator()(const core::IObject2D& below, const core::IObject2D& above) const {
        return below.depthIndex >= above.depthIndex;
    }
}