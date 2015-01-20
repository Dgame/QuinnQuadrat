#include "LevelManager.hpp"
#include "Level.hpp"
#include "TileMap.hpp"
#include "SDL-Framework/Renderer.hpp"

LevelManager::LevelManager() {
	// _level.push_back(new FirstLevel());
	// _level.push_back(new SecondLevel());
}

LevelManager::~LevelManager() {
	for (Level* lvl : _level) {
		delete lvl;
	}
}
