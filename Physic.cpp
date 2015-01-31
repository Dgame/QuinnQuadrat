#include "Physic.hpp"
#include "SDL-Framework/Sprite.hpp"
#include "TileMap.hpp"
#include "Tile.hpp"
#include "Entity.hpp"

namespace Physic {
    bool isOnWalkableGround(sdl::RendererSprite* sprite, TileMap* map) {
        if (!sprite || !map)
            return false;

        const sdl::Vector2i bottom = sprite->getClipRect().getEdgePosition(sdl::Rect::Edge::Bottom);
        const Tile* tile = map->getTileAt(bottom);

        return tile && (tile->mask & Tile::Gras);
    }

    bool isNextOnWalkableGround(Entity* entity, TileMap* map) {
        if (!map || !entity)
            return false;

        sdl::Vector2i bottom = entity->sprite->getClipRect().getEdgePosition(sdl::Rect::Edge::Bottom);
        bottom.x += static_cast<i8_t>(entity->viewDirection) * Tile::Size;

        const Tile* tile = map->getTileAt(bottom);

        return tile && (tile->mask & Tile::Gras);
    }

    bool gravityEffect(sdl::RendererSprite* sprite, TileMap* map) {
        if (!sprite || !map)
            return false;

        // gravity only apply if we are not on walkable ground
        if (!isOnWalkableGround(sprite, map)) {
            sprite->position.y += Force::Gravity;
            return true;
        }

        return false;
    }

    bool jumpEffect(Entity* entity, TileMap* map) {
        if (!map || !entity)
            return false;

        if (entity->isJumping()) {
            // if not jumped right now (and therefore probably from a valid tile), let's check if we reached a Tile
            if (!entity->hasJumped()) {
                if (isOnWalkableGround(entity->sprite, map)) {
                    entity->stopJump();
                    return false;
                }
            }
            
            entity->sprite->position.y -= entity->getJumpForce();
            entity->reduceJump();

            return true;
        }

        return false;
    }
}