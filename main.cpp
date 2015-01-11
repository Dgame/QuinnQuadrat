#include "Framework/Window.hpp"
#include "Framework/Renderer.hpp"
#include "Framework/Event.hpp"
#include "Framework/Color.hpp"
#include "Framework/Sprite.hpp"
#include "Framework/Surface.hpp"
#include "Framework/Timer.hpp"

#undef main

#include "Level.hpp"
#include "TileMap.hpp"

#include <iostream>

int main() {
	sdl::Window wnd("Test-App", sdl::Vector2i(100, 100), 768, 480);
	sdl::Renderer* rend = wnd.createRenderer(SDL_RENDERER_ACCELERATED);
	rend->setDrawColor(sdl::Color::White);
/*
	sdl::Texture* tile_gras = sdl::Surface("media/Tiles-4/Tileset-Bottom-Gras.png").asTextureOf(rend);
	sdl::Rect tile_dst(10, 10, 96, 32);
*/
	Level lvl;
	lvl.loadNext(rend);

	sdl::Timer timer;
	timer.start();
	f32_t fps = 0;

	sdl::Event event;
	while (wnd.isValid()) {
		if (timer.getTicks() >= 1000) {
			timer.start();
			std::cout << "FPS: " << fps << std::endl;
			fps = 0;
		} else
			fps++;

		while (sdl::PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.key) {
					case SDLK_ESCAPE:
						wnd.close();
					break;
					case SDLK_DOWN:
						
					break;
					case SDLK_UP:
					
					break;
					case SDLK_LEFT:

					break;
					case SDLK_RIGHT:

					break;
					case SDLK_SPACE:
						
					break;
				}
			} else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE) {
				wnd.close();
			}
		}

		rend->clear();
		rend->draw(*lvl.map);
		//rend->copy(tile_gras, &tile_dst, nullptr);
		rend->present();
	}
}