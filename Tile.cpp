#include "Tile.hpp"
#include <cmath>
#include <iostream>

#define TILE_SIZE 32
#define TILESET_WIDTH 96
#define TILESET_HEIGHT 128

const u16_t TileSetMasks[] = {
	(Tile::LeftEdge | Tile::Gras),					Tile::Gras, 					(Tile::RightEdge | Tile::Gras),
	(Tile::LeftEdge | Tile::Gras | Tile::Brittle),	(Tile::Gras | Tile::Brittle),	(Tile::RightEdge | Tile::Gras | Tile::Brittle),
	(Tile::LeftEdge | Tile::Stone),					Tile::Stone,					(Tile::RightEdge | Tile::Stone),
	(Tile::LeftEdge | Tile::Stone | Tile::Brittle),	(Tile::Stone | Tile::Brittle), 	(Tile::RightEdge | Tile::Stone | Tile::Brittle)
};

Tile::Tile(u16_t index, sdl::Texture* tex, const sdl::Vector2i& pos) : sdl::Sprite(tex, pos * TILE_SIZE) {
	const u16_t val = (index - 1) * TILE_SIZE;

	this->sourceRect.x = (val % TILESET_WIDTH);
	this->sourceRect.y = (val / TILESET_WIDTH) * TILE_SIZE;
	this->sourceRect.width = TILE_SIZE;
	this->sourceRect.height = TILE_SIZE;

	this->id = TileSetMasks[index - 1];
}