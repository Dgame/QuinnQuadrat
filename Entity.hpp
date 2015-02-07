#ifndef GAME_ENTITY_HPP
#define GAME_ENTITY_HPP

#include "SDL-Framework/types.hpp"

namespace sdl {
    class RendererSprite;
}

enum class Direction : i8_t {
    Left = -1,
    Right = 1
};

struct Entity {
    sdl::RendererSprite* sprite;
    Direction viewDirection = Direction::Right;
    u16_t moving = 0;

    explicit Entity(sdl::RendererSprite*);
    virtual ~Entity();

    void move(Direction dir) {
        if (!this->isMoving()) {
            this->moving = 1;
            this->viewDirection = dir;
        }
    }

    bool isMoving() const {
        return this->moving > 0;
    }

    void reverseDirection();
    void roll();
};

#endif