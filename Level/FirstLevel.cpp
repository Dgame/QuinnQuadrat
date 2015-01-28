#include "FirstLevel.hpp"
#include "../SDL-Framework/RendererSprite.hpp"

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

void FirstLevel::interaction(sdl::RendererSprite&) {

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