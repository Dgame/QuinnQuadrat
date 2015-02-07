#include "Entity.hpp"
#include "Physic.hpp"
#include "SDL-Framework/RendererSprite.hpp"
#include <SDL.h>

Entity::Entity(sdl::RendererSprite* spr) : sprite(spr) {

}

Entity::~Entity() {
    delete this->sprite;
}

void Entity::reverseDirection() {
    switch (this->viewDirection) {
        case Direction::Left:
            this->viewDirection = Direction::Right;
        break;

        case Direction::Right:
            this->viewDirection = Direction::Left;
        break;

        default: break;
    }
}

void Entity::roll() {
    if (this->isMoving()) {
        if (this->viewDirection == Direction::Left) {
            this->sprite->flipMode = SDL_FLIP_VERTICAL;

            this->sprite->position.x -= Physic::Force::Move;
            this->sprite->rotationAngle -= Physic::Force::Rotation;
        } else if (this->viewDirection == Direction::Right) {
            this->sprite->flipMode = 0;

            this->sprite->position.x += Physic::Force::Move;
            this->sprite->rotationAngle += Physic::Force::Rotation;
        }

        this->moving++;
        if (this->moving > Physic::AnimationSteps)
            this->moving = 0;
    }
}