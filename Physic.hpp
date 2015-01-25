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

		const u16_t Jump = 32;
		const u16_t JumpGravity = 8;
		const u16_t JumpMove = 32;
	}

	Tile* getUnderlyingTile(sdl::RendererSprite* sprite, TileMap*);
	bool isInAir(sdl::RendererSprite*, TileMap*);
	bool gravity(sdl::RendererSprite*, TileMap*);
	bool jump(Entity&, TileMap*);
}

#endif