#ifndef SKY_GAME_LEVEL_HPP
#define SKY_GAME_LEVEL_HPP

#include "../Level.hpp"
#include <vector>

struct SkyLevel : public Level {
    std::vector<sdl::RendererSprite*> _sky_clouds;

    virtual ~SkyLevel();

    virtual void init() override;
    virtual void backgroundMotion() override;
    virtual void renderOn(sdl::Renderer*) const override;
};

#endif