#ifndef GAME_TILE_MAP_HPP
#define GAME_TILE_MAP_HPP

#include <vector>
#include <string>

#include "SDL-Framework/types.hpp"

namespace sdl {
    struct Vector2i;

    class Texture;
    class Renderer;
}

struct Tile;

class TileMap {
public:
    explicit TileMap(sdl::Renderer*, const std::string&);
    virtual ~TileMap();

    Tile* getTileAt(const sdl::Vector2i&) const;
    Tile* getTileNear(const sdl::Vector2i&) const;

    u16_t width() const {
        return _width;
    }

    u16_t height() const {
        return _height;
    }

    void renderOn(const sdl::Renderer*) const;

private:
    std::vector<Tile*> _tiles;

    sdl::Texture* _tex;

    u16_t _width;
    u16_t _height;
};

#endif