#include "Level.hpp"
#include "Tiles.hpp"

Level::~Level() {
	for (Tiles* tls : _tiles) {
		delete tls;
	}
}

void Level::addTiles(Tiles* tls) {
	if (tls)
		_tiles.push_back(tls);
}

void Level::renderOn(const sdl::Renderer* rend) const {
	if (!rend)
		return;

	for (const Tiles* tls : _tiles) {
		tls->renderOn(rend);
	}
}

void Level::renderOn(const sdl::Window* wnd) const {
	if (!wnd)
		return;

	for (const Tiles* tls : _tiles) {
		tls->renderOn(wnd);
	}
}