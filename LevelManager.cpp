#include "LevelManager.hpp"
#include "Level.hpp"
#include "TileMap.hpp"
#include "SDL-Framework/Renderer.hpp"

LevelManager::LevelManager() {
	_level.push_back(new Level());
}

Level* LevelManager::loadNext(sdl::Renderer* rend) {
	Level* lvl = nullptr;
	if (_levelNr < _level.size()) {
		lvl = _level[_levelNr];
		_levelNr++;
		
		if (!lvl->build(rend, _levelNr)) {
			std::cerr << "Could not load Level " << _levelNr << std::endl;
			return nullptr;
		}
	}

	return lvl;
}

LevelManager::~LevelManager() {
	for (Level* lvl : _level) {
		delete lvl;
	}
}
