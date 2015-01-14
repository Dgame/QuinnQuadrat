#include "Tile.hpp"
#include <cmath>
#include <iostream>

const u16_t TileSetMasks[] = {
	(Tile::LeftEdge | Tile::Gras),					Tile::Gras, 					(Tile::RightEdge | Tile::Gras),
	(Tile::LeftEdge | Tile::Gras | Tile::Brittle),	(Tile::Gras | Tile::Brittle),	(Tile::RightEdge | Tile::Gras | Tile::Brittle),
	(Tile::LeftEdge | Tile::Stone),					Tile::Stone,					(Tile::RightEdge | Tile::Stone),
	(Tile::LeftEdge | Tile::Stone | Tile::Brittle),	(Tile::Stone | Tile::Brittle), 	(Tile::RightEdge | Tile::Stone | Tile::Brittle)
};

Tile::Tile(u16_t index, sdl::Texture* tex, const sdl::Vector2i& pos) : sdl::Sprite(tex, pos * Tile::Size) {
	const u16_t val = (index - 1) * Tile::Size;

	this->sourceRect.x = (val % Tile::TilesetWidth);
	this->sourceRect.y = (val / Tile::TilesetWidth) * Tile::Size;
	this->sourceRect.width = Tile::Size;
	this->sourceRect.height = Tile::Size;

	this->mask = TileSetMasks[index - 1];
}