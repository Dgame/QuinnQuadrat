#include "Physic.hpp"
#include "SDL-Framework/Sprite.hpp"
#include "TileMap.hpp"
#include "Entity.hpp"
#include <iostream>

namespace Physic {
    bool gravityEffect(Entity& entity, TileMap* map, bool reversed) {
        sdl::Vector2i curPos;
        if (!reversed)
            curPos = entity.sprite->getClipRect().getEdgePosition(sdl::Rect::Edge::Bottom);
        else
            curPos = entity.sprite->getClipRect().getEdgePosition(sdl::Rect::Edge::Top);

        const Tile* tile = map->getTileNear(curPos);

        // gravity only apply if we are not on walkable ground
        if (!tile || !(tile->mask & Tile::Gras)) {
            if (!reversed)
                entity.sprite->position.y += Force::Gravity;
            else
                entity.sprite->position.y -= Force::Gravity;

            return true;
        }

        return false;
    }
}