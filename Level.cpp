#include "Level.hpp"
#include "TileMap.hpp"
#include <sstream>
#include <fstream>

Level::Level() {
	
}

Level::~Level() {
	delete this->map;
}

bool Level::loadNext(sdl::Renderer* rend) {
	_levelNr++;

	std::stringstream buf;
	buf << "media/lvl/Level_" << _levelNr << ".tmx";

	const std::string filename = buf.str();
	FILE* f = fopen(filename.c_str(), "rb");
	if (!f)
		return false;
	fclose(f);

	if (this->map)
		delete this->map;

	this->map = new TileMap(rend, filename);

	return true;
}