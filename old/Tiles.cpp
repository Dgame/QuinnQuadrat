#include "Tiles.hpp"
#include "Framework/Vector2.hpp"
#include "Framework/Texture.hpp"
#include "Framework/Surface.hpp"
#include "Framework/Sprite.hpp"
#include "Framework/Renderer.hpp"
#include "Framework/Window.hpp"

Tiles::~Tiles() {
	for (sdl::Sprite* spr : _tiles) {
		delete spr;
	}
}

void Tiles::createTileAt(const sdl::Vector2i& pos, sdl::Texture* tex) {
	sdl::Sprite* spr = this->getTileAt(pos);
	if (spr)
		spr->setImage(tex);
	else
		_tiles.push_back(new sdl::Sprite(tex, pos));
}

void Tiles::createTileAt(const sdl::Vector2i& pos, sdl::Surface& srfc) {
	sdl::Sprite* spr = this->getTileAt(pos);
	if (spr)
		spr->setImage(srfc);
	else
		_tiles.push_back(new sdl::Sprite(srfc, pos));
}

void Tiles::deleteTileAt(const sdl::Vector2i& pos) {
	u32_t index;
	sdl::Sprite* spr = this->getTileAt(pos, &index);
	if (spr) {
		_tiles[index] = nullptr;
		delete spr;
	}
}

sdl::Sprite* Tiles::releaseTileAt(const sdl::Vector2i& pos) {
	u32_t index;
	sdl::Sprite* spr = this->getTileAt(pos, &index);
	if (spr) {
		_tiles[index] = nullptr;

		return spr;
	}

	return nullptr;
}

sdl::Sprite* Tiles::getTileAt(const sdl::Vector2i& pos, u32_t* index) {
	for (u32_t i = 0; i < _tiles.size(); i++) {
		if (_tiles[i] && _tiles[i]->position == pos) {
			if (index)
				*index = i;
			return _tiles[i];
		}
	}

	return nullptr;
}

void Tiles::move(u32_t ox, u32_t oy) {
	for (sdl::Sprite* spr : _tiles) {
		spr->position.x += ox;
		spr->position.y += oy;
	}
}

void Tiles::move(const sdl::Vector2i& offset) {
	for (sdl::Sprite* spr : _tiles) {
		spr->position += offset;
	}
}

void Tiles::renderOn(const sdl::Renderer* rend) const {
	if (!rend)
		return;

	for (const sdl::Sprite* spr : _tiles) {
		rend->draw(*spr);
	}
}

void Tiles::renderOn(const sdl::Window* wnd) const {
	if (!wnd)
		return;

	for (const sdl::Sprite* spr : _tiles) {
		wnd->draw(*spr);
	}
}