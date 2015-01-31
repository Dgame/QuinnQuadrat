#ifndef GAME_LEVEL_1_HPP
#define GAME_LEVEL_1_HPP

#include "SkyLevel.hpp"

class Entity;

struct FirstLevel : public SkyLevel {
    std::vector<sdl::RendererSprite*> _entnervte_ellipsen;
    std::vector<Entity*> _geo_gauner;

    virtual ~FirstLevel();

    virtual void init() override;
    virtual void backgroundMotion() override;
    virtual void interaction(Entity&) override;
    virtual void renderOn(sdl::Renderer*) const override;
};

#endif