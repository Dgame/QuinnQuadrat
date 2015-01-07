#ifndef GAME_TILE_HPP
#define GAME_TILE_HPP

#include "Framework/types.hpp"
#include "Framework/Sprite.hpp"

struct Tile : public sdl::Sprite {
    explicit Tile(u16_t, sdl::Texture*, const sdl::Vector2i&);
    virtual ~Tile() { }
};

#endif