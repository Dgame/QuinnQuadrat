#include "FirstLevel.hpp"
#include "../SDL-Framework/RendererSprite.hpp"
#include "../SDL-Framework/Surface.hpp"
#include "../SDL-Framework/Texture.hpp"
#include "../SDL-Framework/Renderer.hpp"

FirstLevel::~FirstLevel() {
	for (sdl::RendererSprite* gg : _geo_gauner) {
		delete gg;
	}

	for (sdl::RendererSprite* ee : _entnervte_ellipsen) {
		delete ee;
	}
}

void  FirstLevel::init() {
	_geo_gauner.push_back(new sdl::RendererSprite(Level::GeoGauner, sdl::Vector2i(256, 36)));
}

void FirstLevel::interaction(sdl::RendererSprite&) {

}

void FirstLevel::renderOn(sdl::Renderer* rend) const {
	Level::renderOn(rend);

	for (sdl::RendererSprite* gg : _geo_gauner) {
		rend->draw(*gg);
	}

	for (sdl::RendererSprite* ee : _entnervte_ellipsen) {
		rend->draw(*ee);
	}
}