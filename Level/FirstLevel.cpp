#include "FirstLevel.hpp"
#include "../SDL-Framework/RendererSprite.hpp"
#include "../Entity.hpp"
#include "../Physic.hpp"

void FirstLevel::init() {
    SkyLevel::init();

    std::vector<LevelData> data;
    this->loadData(data);

    for (const LevelData& lvl_data : data) {
        if (lvl_data.type == "gg") {
            auto sprite = new sdl::RendererSprite(Level::GeoGauner, lvl_data.position);
            auto ent = new Entity(sprite);
            ent->move(Direction::Left);

            _geo_gauner.push_back(ent);
        }
    }
}

void FirstLevel::restore() {
    for (Entity* gg : _geo_gauner) {
        gg->restore();
    }
}

void FirstLevel::backgroundMotion() {
    SkyLevel::backgroundMotion();

    for (Entity* gg : _geo_gauner) {
        if (gg->isDead())
            continue;

        switch (gg->state) {
            case State::Alive:
                if (!gg->isMoving()) {
                    gg->moving = 1;

                    Physic::bounceEffect(*gg, *this->map);
                }

                gg->roll();
            break;

            case State::Hurt:
                if (!Physic::dropEffect(*gg))
                    gg->state = State::Dead;
            break;

            case State::Dead: break;
        }
    }
}

void FirstLevel::interaction(Entity& ent) {
    if (ent.sprite->position.x >= 800 && 
        (ent.sprite->position.y == 320 || ent.sprite->position.y == 352))
    {
        this->finished = true;
    }

    const sdl::Rect clipRect = ent.sprite->getClipRect();

    for (Entity* gg : _geo_gauner) {
        if (gg->isDead())
            continue;

        if (gg->sprite->getClipRect().intersectWith(clipRect)) {
            if (gg->sprite->position.y > ent.sprite->position.y) {
                gg->state = State::Hurt;
                gg->sprite->rotationAngle = 180;
                gg->moving = 0;
            } else
                ent.state = ent.state == State::Hurt ? State::Dead : State::Hurt;
        }
    }
}

void FirstLevel::renderOn(sdl::Renderer* rend) const {
    SkyLevel::renderOn(rend);

    for (Entity* gg : _geo_gauner) {
        if (gg->isDead())
            continue;

        gg->sprite->renderOn(rend);
    }
}