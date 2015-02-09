#ifndef GAME_LEVEL_HPP
#define GAME_LEVEL_HPP

#include "SDL-Framework/types.hpp"
#include "SDL-Framework/Vector2.hpp"
#include <string>
#include <vector>

namespace sdl {
    class Texture;
    class Renderer;
}

class TileMap;
class Entity;

struct LevelData {
    sdl::Vector2i position;
    std::string type;
};

struct Level {
    static sdl::Texture* GeoGauner;
    static sdl::Texture* SkyCloud;
    // static sdl::Texture* EntnervteEllipse;
    
    TileMap* map = nullptr;
    u16_t lvlNr = 0;
    bool finished = false;
    bool freezed = false;

    virtual ~Level();

    bool build(sdl::Renderer*, u16_t);
    void loadData(std::vector<LevelData>&);

    virtual void init() { }
    virtual void backgroundMotion() { }
    virtual void interaction(Entity&) { }

    virtual void renderOn(sdl::Renderer*) const;
};

#endif