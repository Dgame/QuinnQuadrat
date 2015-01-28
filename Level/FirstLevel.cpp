#include "FirstLevel.hpp"
#include "../SDL-Framework/RendererSprite.hpp"
#include "../Entity.hpp"

FirstLevel::~FirstLevel() {
    for (sdl::RendererSprite* gg : _geo_gauner) {
        delete gg;
    }

    for (sdl::RendererSprite* ee : _entnervte_ellipsen) {
        delete ee;
    }
}

void FirstLevel::init() {
    SkyLevel::init();

    _geo_gauner.push_back(new sdl::RendererSprite(Level::GeoGauner, sdl::Vector2i(256, 36)));
}

void FirstLevel::backgroundMotion() {
    SkyLevel::backgroundMotion();
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

    for (sdl::RendererSprite* gg : _geo_gauner) {
        gg->renderOn(rend);
    }

    for (sdl::RendererSprite* ee : _entnervte_ellipsen) {
        ee->renderOn(rend);
    }
}