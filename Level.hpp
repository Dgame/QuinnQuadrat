#ifndef GAME_LEVEL_HPP
#define GAME_LEVEL_HPP

#include "Framework/types.hpp"

namespace sdl {
	class Renderer;
}

class TileMap;

class Level {
public:
	Level();
	virtual ~Level();
	
    bool loadNext(sdl::Renderer*);

    u16_t curLvlNr() const {
    	return _levelNr;
    }
    
private:
    u16_t _levelNr = 0;

public:
	TileMap* map = nullptr;
};

#endif