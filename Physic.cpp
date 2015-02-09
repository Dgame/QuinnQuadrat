#include "Physic.hpp"
#include "SDL-Framework/Sprite.hpp"
#include "TileMap.hpp"
#include "Entity.hpp"
#include <iostream>

namespace Physic {
    bool outOfBounds(Entity& entity) {
        if (entity.sprite->position.x < 0
            || entity.sprite->position.x > WorldWidth)
        {
            return true;
        }

        if (entity.sprite->position.y < (Tile::Size * -5)
            || entity.sprite->position.y > (WorldHeight + (Tile::Size * 5)))
        {
            return true;
        }

        return false;
    }

    bool dropEffect(Entity& entity, bool reversed) {
        if (!reversed)
            entity.sprite->position.y += Force::Gravity;
        else
            entity.sprite->position.y -= Force::Gravity;

        return outOfBounds(entity);
    }

    bool gravityEffect(Entity& entity, TileMap& map, bool reversed) {
        sdl::Edge spriteEdge, tileEdge;
        if (!reversed) {
            spriteEdge = sdl::Edge::Bottom;
            tileEdge = sdl::Edge::Top;
        } else {
            spriteEdge = sdl::Edge::Top;
            tileEdge = sdl::Edge::Bottom;
        }

        const sdl::Vector2i curPos = entity.sprite->getClipRect().getEdgePosition(spriteEdge);
        const Tile* tile = map.getTileAt(curPos, tileEdge);

        // gravity only apply if we are not on walkable ground
        if (!tile || !(tile->mask & Tile::Gras)) {
            dropEffect(entity, reversed);

            return true;
        }

        return false;
    }

    bool bounceEffect(Entity& entity, TileMap& map) {
        sdl::Vector2i curPos = entity.sprite->getClipRect().getEdgePosition(sdl::Edge::Bottom);
        if (entity.viewDirection == Direction::Left)
            curPos.x -= Tile::Size;
        else
            curPos.x += Tile::Size;

        const Tile* tile = map.getTileAt(curPos, sdl::Edge::Top);
        if (!tile || !(tile->mask & Tile::Gras)) {
            entity.reverseDirection();

            return true;
        }

        return false;
    }
}