#ifndef GAME_LEVEL_HPP
#define GAME_LEVEL_HPP

#include "SDL-Framework/types.hpp"

namespace sdl {
	class Renderer;
}

class TileMap;

struct Level {
	TileMap* map = nullptr;

	virtual ~Level();

	bool build(sdl::Renderer*, u16_t);
	virtual void run() { }
};

#endif