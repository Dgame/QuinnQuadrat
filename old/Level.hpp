#ifndef SDL_LEVELS_HPP
#define SDL_LEVELS_HPP

#include <vector>
#include "Framework/Drawable.hpp"

namespace sdl {
	struct Event;
}

class Tiles;

class Level : public sdl::Drawable {
public:
	virtual ~Level();

	void addTiles(Tiles*);

	virtual void renderOn(const sdl::Renderer*) const override;
	virtual void renderOn(const sdl::Window*) const override;

	virtual void handleEvent(sdl::Event*) = 0;

public:
	// TODO: characters...
	std::vector<Tiles*> _tiles;
};

#endif