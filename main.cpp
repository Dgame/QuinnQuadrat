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
#include "Tile.hpp"
#include "Physic.hpp"

#include <iostream>

const u16_t MaxFPS = 60;
const u16_t TicksPerFrame = 1000 / MaxFPS;

int main() {
	// Window
	sdl::Window wnd("Test-App", sdl::Vector2i(100, 100), 768, 480);
	sdl::Renderer* rend = wnd.createRenderer(SDL_RENDERER_ACCELERATED);
	rend->setDrawColor(sdl::Color::White);

	// Level
	Level lvl;
	lvl.loadNext(rend);

	// Sprites
	sdl::Texture* quinn_tex = sdl::Surface("media/Quinn-Quadrat.png").asTextureOf(rend);
	sdl::Vector2i quinnStartPos(96, 8);
	sdl::Sprite quinn(quinn_tex, quinnStartPos);

	// Timer
	sdl::Timer timer;
	timer.start();

	/*
	// FPS Timer
	sdl::Timer fpsTimer;
	fpsTimer.start();
	f32_t fps = 0;
	*/

	// Game Loop
	sdl::Event event;
	while (wnd.isValid()) {
		/*
		if (fpsTimer.getTicks() >= 1000) {
			fpsTimer.start();
			std::cout << "FPS: " << fps << std::endl;
			fps = 0;
		} else
			fps++;
		*/
		const u32_t frameTicks = timer.getTicks();
		if (frameTicks < TicksPerFrame) {
			SDL_Delay(TicksPerFrame - frameTicks);
			timer.start();
		}

		bool moved = false;
		bool gravity = false;

		while (sdl::PollEvent(&event) && !gravity) {
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
						gravity = Physic::gravity(&quinn, lvl.map);
						if (!gravity) {
							quinn.position.x -= Tile::Size;
							quinn.rotationAngle -= 90;

							moved = true;
						}
					break;

					case SDLK_RIGHT:
						gravity = Physic::gravity(&quinn, lvl.map);
						if (!gravity) {
							quinn.position.x += Tile::Size;
							quinn.rotationAngle += 90;

							moved = true;
						}
					break;

					case SDLK_SPACE:
						
					break;
				}
			} else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE) {
				wnd.close();
			}
		}

		if (!moved && !gravity)
			Physic::gravity(&quinn, lvl.map);

		if (quinn.position.y < 0 || 
			static_cast<u32_t>(quinn.position.y) > wnd.height())
		{
			SDL_Delay(1000);
			timer.start();
			quinn.position = quinnStartPos;
		}

		rend->clear();
		rend->draw(*lvl.map);
		rend->draw(quinn);
		rend->present();
	}
}