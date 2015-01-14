#include "Physic.hpp"
#include "Framework/Sprite.hpp"
#include "TileMap.hpp"
#include "Tile.hpp"

namespace Physic {
	bool gravity(sdl::Sprite* sprite, TileMap* map) {
		if (!sprite || !map)
			return false;

		const sdl::Vector2i bottomLeft = sprite->getClipRect().getEdgePosition(sdl::Rect::Edge::BottomLeft);

		const Tile* tile = map->getTileAt(bottomLeft);
		if (!tile || !(tile->mask & Tile::Gras)) {
			sprite->position.y += Force::Gravity;
			return true;
		}

		return false;
	}
}