#ifndef GAME_PHYSIC_HPP
#define GAME_PHYSIC_HPP

#include "Framework/types.hpp"

namespace sdl {
	class Sprite;
}

class TileMap;

namespace Physic {
	namespace Force {
		const u16_t Gravity = 4;
		const u16_t Jump = 20;
	}

	bool gravity(sdl::Sprite*, TileMap*);
}

#endif