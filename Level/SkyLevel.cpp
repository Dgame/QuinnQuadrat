#include "SkyLevel.hpp"
#include "../SDL-Framework/RendererSprite.hpp"

#include <random>

SkyLevel::~SkyLevel() {
    for (sdl::RendererSprite* sc : _sky_clouds) {
        delete sc;
    }
}

void SkyLevel::init() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disx(0, 800);
    std::uniform_int_distribution<> disy(0, 200);
 
    for (i16_t i = 0; i < 12; ++i) {
        const i16_t x = disx(gen);
        const i16_t y = disy(gen);

        // std::cout << "x: " << x << ", y: " << y << std::endl;

        _sky_clouds.push_back(new sdl::RendererSprite(Level::SkyCloud, sdl::Vector2i(x, y)));
    }
}

void SkyLevel::backgroundMotion() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disx(-200, 10);
    std::uniform_int_distribution<> disy(0, 200);

    for (sdl::RendererSprite* sc : _sky_clouds) {
        const i16_t x = disx(gen);
        const i16_t y = disy(gen);

        sc->position.x += 1;
        if (sc->position.x > 800) {
            sc->position.x = x;
            sc->position.y = y;

            // std::cout << "x: " << x << ", y: " << y << std::endl;
        }
    }
}

void SkyLevel::renderOn(sdl::Renderer* rend) const {
    Level::renderOn(rend);

    for (sdl::RendererSprite* sc : _sky_clouds) {
        sc->renderOn(rend);
    }
}