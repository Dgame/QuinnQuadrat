#include "Framework/Window.hpp"
#include "Framework/Renderer.hpp"
#include "Framework/Event.hpp"
#include "Framework/Color.hpp"
#include "Framework/Sprite.hpp"
#include "Framework/Surface.hpp"
#include "Framework/Timer.hpp"

#include "Level.hpp"
#include "LevelManager.hpp"

#undef main

#include <iostream>

int main() {
	sdl::Window wnd("Test-App", sdl::Vector2i(100, 100), 640, 480);
	sdl::Renderer* rend = wnd.createRenderer(SDL_RENDERER_ACCELERATED);
	rend->setDrawColor(sdl::Color::White);

	LevelManager lvl_manager(rend);
	lvl_manager.load(0);

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
		if (lvl_manager.getCurrentLevel())
			lvl_manager.getCurrentLevel()->renderOn(rend);
		rend->present();
	}
}