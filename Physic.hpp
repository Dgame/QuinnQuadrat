#ifndef GAME_PHYSIC_HPP
#define GAME_PHYSIC_HPP

#include "Framework/types.hpp"

namespace sdl {
	class Sprite;
}

class TileMap;
struct Tile;

namespace Physic {
	namespace Force {
		const u16_t Gravity = 8;
		const u16_t Move = 32;

		const u16_t Jump = 32;
		const u16_t JumpGravity = 8;
		const u16_t JumpMove = 96;
	}

	Tile* getUnderlyingTile(sdl::Sprite* sprite, TileMap*);
	bool gravity(sdl::Sprite*, TileMap*);
	bool jump(sdl::Sprite*, TileMap*, bool);
}

#endif