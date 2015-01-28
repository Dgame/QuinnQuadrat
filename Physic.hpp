#ifndef GAME_PHYSIC_HPP
#define GAME_PHYSIC_HPP

#include "SDL-Framework/types.hpp"

namespace sdl {
	class RendererSprite;
}

class TileMap;
class Entity;
struct Tile;

namespace Physic {
	namespace Force {
		const u16_t Gravity = 4;
		
		const u16_t Move = 32;
		const u16_t MoveRotation = 90;

		const u16_t Jump = 28;
	}

	Tile* getUnderlyingTile(sdl::RendererSprite* sprite, TileMap*);
	bool isOnWalkableGround(sdl::RendererSprite*, TileMap*);
	bool gravityEffect(sdl::RendererSprite*, TileMap*);
	bool jumpEffect(Entity&, TileMap*);
}

#endif