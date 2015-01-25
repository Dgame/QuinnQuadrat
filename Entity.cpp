#include "Entity.hpp"
#include "Physic.hpp"
#include "SDL-Framework/RendererSprite.hpp"

Entity::Entity(sdl::RendererSprite* spr) : sprite(spr) {

}

Entity::~Entity() {
	delete this->sprite;
}

void Entity::jump() {
	_jumpForce = Physic::Force::Jump;
}

bool Entity::hasJumped() const {
	return _jumpForce == Physic::Force::Jump;
}

void Entity::reduceJump() {
	if (this->isJumping())
		_jumpForce -= Physic::Force::JumpGravity;
}

void Entity::roll() {
	if (this->hasMoved()) {
		if (_dir == Direction::Left) {
			this->sprite->position.x -= Physic::Force::Move;
			this->sprite->rotationAngle -= Physic::Force::MoveRotation;
		} else if (_dir == Direction::Right) {
			this->sprite->position.x += Physic::Force::Move;
			this->sprite->rotationAngle += Physic::Force::MoveRotation;
		}

		this->stopMove();
	}
}