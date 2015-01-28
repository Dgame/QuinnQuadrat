#ifndef GAME_ENTITY_HPP
#define GAME_ENTITY_HPP

#include "SDL-Framework/types.hpp"

namespace sdl {
    class RendererSprite;
}

enum class Direction : i8_t {
    None,
    Left,
    Right
};

class Entity {
public:
    sdl::RendererSprite* sprite;

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

    Direction getDir() const {
        return _dir;
    }

    bool hasMoved() const {
        return _dir != Direction::None;
    }

    void move(Direction the_dir) {
        _dir = the_dir;
    }

    void stopMove() {
        _dir = Direction::None;
    }

    void roll();

private:
    Direction _dir = Direction::None;
    i16_t _jumpForce = 0;
};

#endif