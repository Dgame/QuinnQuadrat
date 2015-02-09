#ifndef GAME_ENTITY_HPP
#define GAME_ENTITY_HPP

#include "SDL-Framework/types.hpp"
#include "SDL-Framework/Vector2.hpp"

namespace sdl {
    class RendererSprite;
}

enum class Direction {
    Left = -1,
    Right = 1
};

enum class State {
    Alive,
    Hurt,
    Dead
};

struct Entity {
    sdl::Vector2i startPosition;

    sdl::RendererSprite* sprite;
    Direction viewDirection = Direction::Right;
    State state = State::Alive;
    u16_t moving = 0;

    explicit Entity(sdl::RendererSprite*);
    virtual ~Entity();

    void restore();

    void move(Direction dir) {
        if (!this->isMoving() && !this->isDead()) {
            this->moving = 1;
            this->viewDirection = dir;
        }
    }

    bool isMoving() const {
        return this->moving > 0;
    }

    bool isAlive() const {
        return this->state == State::Alive || this->state == State::Hurt;
    }

    bool isHurt() const {
        return this->state == State::Hurt;
    }

    bool isDead() const {
        return this->state == State::Dead;
    }

    void reverseDirection();
    void roll();
};

#endif