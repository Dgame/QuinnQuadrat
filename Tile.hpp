#ifndef GAME_TILE_HPP
#define GAME_TILE_HPP

#include "SDL-Framework/types.hpp"
#include "SDL-Framework/RendererSprite.hpp"

struct Tile : public sdl::RendererSprite {
    static const u16_t Size = 32;
    static const u16_t TilesetWidth = 96;
    static const u16_t TilesetHeight = 128;

    enum Mask {
        LeftEdge = 0x001,
        RightEdge = 0x002,
        Edge = LeftEdge | RightEdge,
        Stone = 0x004,
        Gras = 0x008,
        Brittle = 0x010
    };

    u8_t mask;
    
    explicit Tile(u16_t, sdl::Texture*, const sdl::Vector2i&);
    virtual ~Tile() { }
};

#endif