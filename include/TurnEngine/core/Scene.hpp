#pragma once

#include <vector>
#include "TurnEngine/core/Object2D.hpp"
#include "TurnEngine/render/Drawer.hpp"

namespace TurnEngine::core {
    /// @brief
    /// Class represents scene.
    /// Scene stores 2D objects.
    /// And allows to manage that objects
    class Scene : public Object2D {
    private:
        std::vector<Object2D *> objects;
        Point<int> pos;
    public:
        /// @brief
        /// the constructor
        /// @param Point<int> pos
        /// @param int width
        /// @param int height
        Scene(Point<int> pos, int width, int height);

        /// @brief
        /// method contains tells if point inside scene
        /// @param Point<int> pos
        /// @return `true` if point inside scene, else `false`
        bool contains(Point<int> pos);

        /// @brief
        /// method draws all child 2D objects inside scene
        /// @param Drawer* drawer
        void draw(render::Drawer *drawer) override;

        /// @brief
        /// method adds child 2D objects to scene
        /// @param Object2D* obj
        void addChild(Object2D *obj);

        /// @brief
        /// method returns all child 2D objects
        /// @return std::vector<Object2D*>
        std::vector<Object2D *> getChildren();

        /// @brief
        /// method returns child 2D object by its name
        /// @param std::string _name
        /// @return Object2D*
        Object2D *getChild(std::string _name) override;

        /// @brief
        /// method returns scene position
        /// @return Object2D*
        Point<int> getPosition();

        /// @brief
        /// method removes child 2D object
        /// @param Object2D* obj
        void removeChild(Object2D *obj);

        /// @brief
        /// method retranslate event signal to child 2D objects
        /// @param Event* _event
        void update(Event *_event) override;
    };
}