#include "Physic.hpp"
#include "SDL-Framework/Sprite.hpp"
#include "TileMap.hpp"
#include "Tile.hpp"

namespace Physic {
	static i16_t jumpForce = 0;

	Tile* getUnderlyingTile(sdl::Sprite* sprite, TileMap* map) {
		if (!sprite || !map)
			return nullptr;

		const sdl::Vector2i bottomLeft = sprite->getClipRect().getEdgePosition(sdl::Rect::Edge::BottomLeft);

		return map->getTileAt(bottomLeft);
	}

	bool gravity(sdl::Sprite* sprite, TileMap* map) {
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

	bool jump(sdl::Sprite* sprite, TileMap* map, bool jumped) {
		if (!sprite || !map)
			return false;

		// if we jumped right now and we aren't jumping currently
		if (jumped && jumpForce <= 0)
			jumpForce = Force::Jump;

		if (jumpForce > 0) {
			// if not jumped right now (and therefore probably from a valid tile), let's check if we reached a Tile
			if (!jumped) {
				// TODO: check overlying Tile?
				const Tile* tile = getUnderlyingTile(sprite, map);
				if (tile && (tile->mask & Tile::Gras)) {
					jumpForce = 0;

					return false;
				}
			}

			sprite->position.y -= jumpForce;
			jumpForce -= Force::JumpGravity;

			return true;
		}

		return false;
	}
}