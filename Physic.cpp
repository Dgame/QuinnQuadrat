#include "Physic.hpp"
#include "SDL-Framework/Sprite.hpp"
#include "TileMap.hpp"
#include "Entity.hpp"
#include <iostream>

namespace Physic {
    namespace {
        bool isOnWalkableTile(Entity& entity, TileMap* map) {
            const sdl::Vector2i curPos = entity.sprite->getClipRect().getEdgePosition(sdl::Rect::Edge::Bottom);
            const Tile* tile = map->getTileNear(curPos);

            return tile && (tile->mask & Tile::Gras);
        }
    }

    bool gravityEffect(Entity& entity, TileMap* map) {
        // gravity only apply if we are not on walkable ground
        if (!isOnWalkableTile(entity, map)) {
            entity.sprite->position.y += Force::Gravity;
            return true;
        }

        return false;
    }

    bool jumpEffect(Entity& entity, TileMap* map) {
        if (entity.jumping) {
            // if not jumped right now (and therefore probably from a valid tile), let's check if we reached a Tile
            if (entity.jumping > 1) {
                if (isOnWalkableTile(entity, map)) {
                    std::cout << "-- End of Jump --" << std::endl;
                    entity.jumping = 0;
                    entity.moving = 0;

                    return false;
                }
            }

            if (entity.moving && (entity.jumping % 2) == 0) {
                std::cout << "MOVE while jumping: " << entity.jumping << std::endl;

                if (entity.viewDirection == Direction::Left)
                    entity.sprite->position.x -= 16;//Physic::Force::Move;
                else
                    entity.sprite->position.x += 16;//Physic::Force::Move;
            }

            if (entity.jumping > Physic::AnimationSteps)
                entity.sprite->position.y += Physic::Force::Jump;
            else
                entity.sprite->position.y -= Physic::Force::Jump;

            entity.jumping++;

            return true;
        }

        return false;
    }
}