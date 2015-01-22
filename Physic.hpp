#ifndef GAME_PHYSIC_HPP
#define GAME_PHYSIC_HPP

#include "SDL-Framework/types.hpp"

namespace sdl {
	class Sprite;
}

class TileMap;
struct Tile;

namespace Physic {
	namespace Force {
		const u16_t Gravity = 4;
		const u16_t Move = 32;

		const u16_t Jump = 64;
		const u16_t JumpGravity = 24;
		const u16_t JumpMove = 128;
	}

	Tile* getUnderlyingTile(sdl::Sprite* sprite, TileMap*);
	bool gravity(sdl::Sprite*, TileMap*);
	bool jump(sdl::Sprite*, TileMap*, bool);
}

#endif