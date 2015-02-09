#ifndef GAME_PHYSIC_HPP
#define GAME_PHYSIC_HPP

#include "SDL-Framework/types.hpp"
#include "Tile.hpp"

namespace sdl {
    enum class Edge;
}

class TileMap;
class Entity;

namespace Physic {
    const u16_t AnimationSteps = 8;
    const u16_t WorldWidth = 800;
    const u16_t WorldHeight = 480;

    namespace Force {
        const u16_t Move = Tile::Size / AnimationSteps;
        const u16_t Gravity = Tile::Size / AnimationSteps;
        const f32_t Rotation = 90.f / AnimationSteps;
    }

    bool outOfBounds(Entity&);
    bool dropEffect(Entity&, bool reversed = false);
    bool gravityEffect(Entity&, TileMap&, bool reversed = false);
    bool bounceEffect(Entity&, TileMap&);
}

#endif