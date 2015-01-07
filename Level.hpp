#ifndef GAME_LEVEL_HPP
#define GAME_LEVEL_HPP

#include "Framework/types.hpp"
#include "Framework/Drawable.hpp"

class TileMap;

class Level : public sdl::Drawable {
private:
    u16_t _levelNr = 1;
    u16_t _lastLevel = 0;

	TileMap* _map;

public:
	virtual ~Level();
	
    void load();
    void loadNext();

    virtual void renderOn(const sdl::Renderer*) const override;
    virtual void renderOn(const sdl::Window*) const override;
};

#endif