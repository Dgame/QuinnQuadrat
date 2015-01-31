#ifndef GAME_PHYSIC_HPP
#define GAME_PHYSIC_HPP

#include "SDL-Framework/types.hpp"

namespace sdl {
    class RendererSprite;
}

class TileMap;
class Entity;
struct Tile;

namespace Physic {
    namespace Force {
        const u16_t Gravity = 4;
        
        const u16_t Move = 4;
        const u16_t MoveRotation = 11;

        const u16_t Jump = 28;
    }

    bool isOnWalkableGround(sdl::RendererSprite*, TileMap*);
    bool isNextOnWalkableGround(Entity*, TileMap*);

    bool gravityEffect(sdl::RendererSprite*, TileMap*);
    bool jumpEffect(Entity*, TileMap*);
}

#endif