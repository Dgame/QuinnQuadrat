#ifndef GAME_LEVEL_HPP
#define GAME_LEVEL_HPP

#include <vector>
#include "SDL-Framework/types.hpp"

namespace sdl {
	class Texture;
	class Renderer;
	class RendererSprite;
}

class TileMap;

struct Level {
	static sdl::Texture* GeoGauner;

	TileMap* map = nullptr;
	bool finished = false;
	bool freezed = false;

	virtual ~Level();

	bool build(sdl::Renderer*, u16_t);

	virtual void init() { }
	virtual void interaction(sdl::RendererSprite&) { }

	virtual void renderOn(sdl::Renderer*) const;
};

#endif