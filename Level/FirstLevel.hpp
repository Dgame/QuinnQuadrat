#ifndef GAME_LEVEL_1_HPP
#define GAME_LEVEL_1_HPP

#include "../Level.hpp"
#include <vector>

struct FirstLevel : public Level {
	std::vector<sdl::RendererSprite*> _entnervte_ellipsen;
	std::vector<sdl::RendererSprite*> _geo_gauner;

	virtual ~FirstLevel();

	virtual void init() override;
	virtual void interaction(sdl::RendererSprite&) override;
	virtual void renderOn(sdl::Renderer*) const override;
};

#endif