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

    std::vector<LevelData> data;
    this->loadData(data);

    for (const LevelData& lvl_data : data) {
        if (lvl_data.type == "gg") {
            auto sprite = new sdl::RendererSprite(Level::GeoGauner, lvl_data.position);
            auto entity = new Entity(sprite);
            entity->move(Direction::Left);

            _geo_gauner.push_back(entity);
        }
    }
}

void FirstLevel::backgroundMotion() {
    SkyLevel::backgroundMotion();

    for (Entity* gg : _geo_gauner) {
        if (!gg->isMoving()) {
            gg->moving = 1;

            Physic::bounceEffect(*gg, *this->map);
        }

        gg->roll();
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