#ifndef GAME_ENTITY_HPP
#define GAME_ENTITY_HPP

#include "SDL-Framework/types.hpp"

namespace sdl {
    class RendererSprite;
}

enum class Direction : i8_t {
    None = 0,
    Left = -1,
    Right = 1
};

inline Direction reverseDirection(Direction dir) {
    switch (dir) {
        case Direction::Left:
            return Direction::Right;
        case Direction::Right:
            return Direction::Left;
        default:
        case Direction::None:
            return dir;
    }
}

class Entity {
public:
    sdl::RendererSprite* sprite;
    Direction viewDirection = Direction::None;
    bool infiniteMotion = true;

    explicit Entity(sdl::RendererSprite*);
    virtual ~Entity();

    void jump();

    bool isJumping() const {
        return _jumpForce > 0;
    }

    bool hasJumped() const;

    void stopJump() {
        _jumpForce = 0;
    }

    void reduceJump();

    u16_t getJumpForce() const {
        return _jumpForce;
    }

    void roll();

private:
    i16_t _jumpForce = 0;
};

#endif