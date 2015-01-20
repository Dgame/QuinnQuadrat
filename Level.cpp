#include "Level.hpp"
#include "TileMap.hpp"
#include <iostream>
#include <sstream>
#include <fstream>

Level::~Level() {
	delete this->map;
}

bool Level::build(sdl::Renderer* rend, u16_t nr) {
	if (this->map)
		return true;

	std::stringstream buf;
	buf << "media/lvl/Level_" << nr << ".tmx";

	const std::string filename = buf.str();
	FILE* f = fopen(filename.c_str(), "rb");
	if (!f) {
		std::cerr << "No such file: " << filename << std::endl;
		return false;
	}
	fclose(f);

	this->map = new TileMap(rend, filename);

	return true;
}