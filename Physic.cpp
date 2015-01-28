#include "Physic.hpp"
#include "SDL-Framework/Sprite.hpp"
#include "TileMap.hpp"
#include "Tile.hpp"
#include "Entity.hpp"

namespace Physic {
    Tile* getUnderlyingTile(sdl::RendererSprite* sprite, TileMap* map) {
        if (!sprite || !map)
            return nullptr;

        const sdl::Vector2i bottomLeft = sprite->getClipRect().getEdgePosition(sdl::Rect::Edge::BottomLeft);

        return map->getTileAt(bottomLeft);
    }

    bool isOnWalkableGround(sdl::RendererSprite* sprite, TileMap* map) {
        if (!sprite || !map)
            return false;

        const Tile* tile = getUnderlyingTile(sprite, map);
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

    bool jumpEffect(Entity& entity, TileMap* map) {
        if (!map)
            return false;

        if (entity.isJumping()) {
            // if not jumped right now (and therefore probably from a valid tile), let's check if we reached a Tile
            if (!entity.hasJumped()) {
                if (isOnWalkableGround(entity.sprite, map)) {
                    entity.stopJump();
                    return false;
                }
            }
            
            entity.sprite->position.y -= entity.getJumpForce();
            entity.reduceJump();

            return true;
        }

        return false;
    }
}