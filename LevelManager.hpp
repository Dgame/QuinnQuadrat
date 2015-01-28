#ifndef GAME_LEVEL_MANAGER_HPP
#define GAME_LEVEL_MANAGER_HPP

#include <vector>
#include <iostream>
#include "SDL-Framework/types.hpp"

namespace sdl {
    class Renderer;
}

struct Level;
class TileMap;

class LevelManager {
public:
    LevelManager();
    virtual ~LevelManager();

    Level* loadNext(sdl::Renderer*);

    u16_t curLvlNr() const {
        return _levelNr;
    }

private:
    std::vector<Level*> _level;
    u16_t _levelNr = 0;
};

#endif