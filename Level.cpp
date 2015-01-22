#include "Level.hpp"
#include "TileMap.hpp"

#include "SDL-Framework/Surface.hpp"

#include <iostream>
#include <sstream>
#include <fstream>

sdl::Texture* Level::GeoGauner = nullptr;

namespace {
	void initTextures(sdl::Renderer* rend) {
		Level::GeoGauner = sdl::Surface("media/Geo-Gauner.png").asTextureOf(rend);
	} 
}

Level::~Level() {
	delete this->map;
}

bool Level::build(sdl::Renderer* rend, u16_t nr) {
	if (!rend)
		return false;

	if (this->map)
		return true;

	if (!GeoGauner)
		initTextures(rend);

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

void Level::renderOn(sdl::Renderer* rend) const {
	if (this->map)
		this->map->renderOn(rend);
}