#include "Level.hpp"
#include "TileMap.hpp"
#include <sstream>
#include <fstream>

Level::~Level() {
	delete this->map;
}

bool build(sdl::Renderer* rend) {
	if (this->map)
		return true;

	std::stringstream buf;
	buf << "media/lvl/Level_" << _levelNr << ".tmx";

	const std::string filename = buf.str();
	FILE* f = fopen(filename.c_str(), "rb");
	if (!f)
		return false;
	fclose(f);

	this->map = new TileMap(rend, filename);

	return true;
}