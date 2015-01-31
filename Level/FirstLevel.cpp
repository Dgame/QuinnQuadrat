#include "FirstLevel.hpp"
#include "../SDL-Framework/RendererSprite.hpp"
#include "../Entity.hpp"
#include "../Physic.hpp"

FirstLevel::~FirstLevel() {
    for (Entity* gg : _geo_gauner) {
        delete gg;
    }

    for (sdl::RendererSprite* ee : _entnervte_ellipsen) {
        delete ee;
    }
}

void FirstLevel::init() {
    SkyLevel::init();

    auto sprite = new sdl::RendererSprite(Level::GeoGauner, sdl::Vector2i(352, 32));
    auto entity = new Entity(sprite);
    entity->viewDirection = Direction::Left;

    _geo_gauner.push_back(entity);
}

void FirstLevel::backgroundMotion() {
    SkyLevel::backgroundMotion();

    for (Entity* gg : _geo_gauner) {
        gg->roll();
        if (!Physic::isNextOnWalkableGround(gg, this->map))
            gg->viewDirection = reverseDirection(gg->viewDirection);
    }
}

void FirstLevel::interaction(Entity& ent) {
    if (ent.sprite->position.x >= 800 && 
        (ent.sprite->position.y == 320 || ent.sprite->position.y == 352))
    {
        this->finished = true;
    }
}

void FirstLevel::renderOn(sdl::Renderer* rend) const {
    SkyLevel::renderOn(rend);

    for (Entity* gg : _geo_gauner) {
        gg->sprite->renderOn(rend);
    }

    for (sdl::RendererSprite* ee : _entnervte_ellipsen) {
        ee->renderOn(rend);
    }
}