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
    u16_t jumping = 0;
    u16_t moving = 0;

    explicit Entity(sdl::RendererSprite*);
    virtual ~Entity();

    void jump() {
        if (!this->jumping)
            this->jumping = 1;
    }

    void move(Direction dir) {
        if (!this->moving) {
            this->moving = 1;
            this->viewDirection = dir;
        }
    }

    void reverseDirection();
    void roll();
};

#endif