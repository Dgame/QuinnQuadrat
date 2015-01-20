#ifndef GAME_LEVEL_MANAGER_HPP
#define GAME_LEVEL_MANAGER_HPP

#include <vector>
#include <iostream>
#include "types.hpp"

namespace sdl {
	class Renderer;
}

class TileMap;
class Level;

class LevelManager {
public:
	LevelManager();
	virtual ~LevelManager();

	Level* loadNext(sdl::Renderer* rend) const {
		_levelNr++;

		Level* lvl = nullptr;
		if (_level.size() < _levelNr) {
			lvl = _level[_levelNr];
			if (!lvl.build(rend)) {
				std::cerr << "Could not load Level " << _levelNr << std::endl;
				return nullptr;
			}
		}

		return lvl;
	}

    u16_t curLvlNr() const {
    	return _levelNr;
    }

private:
	std::vector<Level*> _level;
	u16_t _levelNr = 0;
};

#endif