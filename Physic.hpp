#ifndef GAME_PHYSIC_HPP
#define GAME_PHYSIC_HPP

#include "SDL-Framework/types.hpp"
#include "Tile.hpp"

class TileMap;
class Entity;

namespace Physic {
    const u16_t AnimationSteps = 8;

    namespace Force {
        const u16_t Move = Tile::Size / AnimationSteps;
        const u16_t Gravity = Tile::Size / AnimationSteps;
        const f32_t Rotation = 90.f / AnimationSteps;
    }

    bool gravityEffect(Entity&, TileMap*, bool reversed = false);
}

#endif