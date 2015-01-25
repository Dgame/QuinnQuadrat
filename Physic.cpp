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

	bool gravity(sdl::RendererSprite* sprite, TileMap* map) {
		if (!sprite || !map)
			return false;

		const Tile* tile = getUnderlyingTile(sprite, map);
		// gravity only apply if we are not on walkable ground
		if (!tile || !(tile->mask & Tile::Gras)) {
			sprite->position.y += Force::Gravity;
			return true;
		}

		return false;
	}

	bool jump(Entity& entity, TileMap* map) {
		if (!map)
			return false;

		if (entity.isJumping()) {
			// if not jumped right now (and therefore probably from a valid tile), let's check if we reached a Tile
			if (!entity.hasJumped()) {
				const Tile* tile = getUnderlyingTile(entity.sprite, map);
				if (tile && (tile->mask & Tile::Gras)) {
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