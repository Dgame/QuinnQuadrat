#include "LevelManager.hpp"
#include "Level.hpp"
#include "Tiles.hpp"

#include "Framework/Renderer.hpp"
#include "Framework/Surface.hpp"
#include "Framework/Texture.hpp"
#include "Framework/Vector2.hpp"

LevelManager::LevelManager(sdl::Renderer* rend) {
	// Material / Tiles
	sdl::Texture* btile_gras_left_edge = sdl::Surface("images/tile-bottom-left-gras.png").asTextureOf(rend);
	sdl::Texture* btile_gras_right_edge = sdl::Surface("images/tile-bottom-right-gras.png").asTextureOf(rend);
	sdl::Texture* btile_gras_midd = sdl::Surface("images/tile-bottom-gras.png").asTextureOf(rend);

	u32_t x, y;

	auto inc = [](u32_t& c) { c += 32; return c; };

	// Level #1
	x = 200;
	y = 250;

	Tiles* tiles = new Tiles();
	tiles->createTileAt(sdl::Vector2i(x, y), btile_gras_left_edge);
	tiles->createTileAt(sdl::Vector2i(inc(x), y), btile_gras_midd);
	tiles->createTileAt(sdl::Vector2i(inc(x), y), btile_gras_midd);
	tiles->createTileAt(sdl::Vector2i(inc(x), y), btile_gras_midd);
	tiles->createTileAt(sdl::Vector2i(inc(x), y), btile_gras_midd);
	tiles->createTileAt(sdl::Vector2i(inc(x), y), btile_gras_right_edge);

	Level* lvl = _createNextLevel();
	lvl->addTiles(tiles);
}

LevelManager::~LevelManager() {
	for (Level* lvl : _lvls) {
		delete lvl;
	}
}

Level* LevelManager::_createNextLevel() {
	Level* lvl = new Level();
	_lvls.push_back(lvl);

	return lvl;
}