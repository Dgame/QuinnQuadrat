#ifndef GAME_TILE_MAP_HPP
#define GAME_TILE_MAP_HPP

#include <vector>

#include "Framework/types.hpp"
#include "Framework/Drawable.hpp"

namespace sdl {
    struct Vector2i;
    class Texture;
}

struct Tile;

class TileMap : public sdl::Drawable {
private:
    std::vector<Tile*> _tiles;

    sdl::Texture* _tex;

    u16_t _width;
    u16_t _height;

public:
    explicit TileMap(const std::string&);
    virtual ~TileMap();

    virtual void renderOn(const sdl::Renderer*) const override;
    virtual void renderOn(const sdl::Window*) const override;

    Tile* getTileAt(const sdl::Vector2i&) const;

    u16_t width() const {
        return _width;
    }

    u16_t height() const {
        return _height;
    }
};

#endif