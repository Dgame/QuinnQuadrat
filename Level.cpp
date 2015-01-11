#include "Level.hpp"
#include "TileMap.hpp"
#include <sstream>

Level::Level() {
	
}

Level::~Level() {
	delete this->map;
}

void Level::loadNext(sdl::Renderer* rend) {
	_levelNr++;

	std::stringstream buf;
	buf << "media/lvl/Level_" << _levelNr << ".tmx";

	if (this->map)
		delete this->map;

	this->map = new TileMap(rend, buf.str());
}