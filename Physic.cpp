#include "Physic.hpp"
#include "SDL-Framework/Sprite.hpp"
#include "TileMap.hpp"
#include "Entity.hpp"
#include <iostream>

namespace Physic {
    bool gravityEffect(Entity& entity, TileMap* map, bool reversed) {
        sdl::Edge spriteEdge, tileEdge;
        if (!reversed) {
            spriteEdge = sdl::Edge::Bottom;
            tileEdge = sdl::Edge::Top;
        } else {
            spriteEdge = sdl::Edge::Top;
            tileEdge = sdl::Edge::Bottom;
        }

        const sdl::Vector2i curPos = entity.sprite->getClipRect().getEdgePosition(spriteEdge);
        const Tile* tile = map->getTileAt(curPos, tileEdge);

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