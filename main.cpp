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
	sdl::Window wnd("Test-App", sdl::Vector2i(100, 100), 800, 480);
	sdl::Renderer* rend = wnd.createRenderer(SDL_RENDERER_ACCELERATED);
	rend->setDrawColor(sdl::Color::White);

	// Level
	Level lvl;
	if (!lvl.loadNext(rend)) {
		std::cerr << "No level found?!" << std::endl;
		return 0;
	}

	// Sprites
	sdl::Texture* quinn_tex = sdl::Surface("media/Quinn-Quadrat.png").asTextureOf(rend);
	sdl::Vector2i quinnStartPos(96, 8);
	sdl::Sprite quinn(quinn_tex, quinnStartPos);

	// Timer
	sdl::Timer timer;
	timer.start();

	// FPS Timer
	sdl::Timer fpsTimer;
	fpsTimer.start();

	u32_t fps = 0;

	// Game Loop
	sdl::Event event;
	while (wnd.isValid()) {
		if (fpsTimer.getTicks() >= 1000) {
			fpsTimer.start();
			std::cout << "FPS: " << fps << std::endl;
			fps = 0;
		} else
			fps++;
		
		const u32_t frameTicks = timer.getTicks();
		if (frameTicks > TicksPerFrame) {
			timer.start();

			bool gravity = false;
			bool moved = false;
			bool jumped = false;

			while (sdl::PollEvent(&event) && !gravity) {
				if (event.type == SDL_KEYDOWN) {
					switch (event.key.key) {
						case SDLK_ESCAPE:
							wnd.close();
						break;

						case SDLK_LEFT:
							gravity = Physic::gravity(&quinn, lvl.map);
							if (!gravity) {
								quinn.position.x -= Physic::Force::Move;
								quinn.rotationAngle -= 90;
								moved = true;
							}
						break;

						case SDLK_RIGHT:
							gravity = Physic::gravity(&quinn, lvl.map);
							if (!gravity) {
								quinn.position.x += Physic::Force::Move;
								quinn.rotationAngle += 90;
								moved = true;
							}
						break;

						case SDLK_UP:
							gravity = Physic::gravity(&quinn, lvl.map);
							if (!gravity)
								jumped = true;
						break;
					}
				} else if (event.type == SDL_WINDOWEVENT &&
					event.window.event == SDL_WINDOWEVENT_CLOSE)
				{
					wnd.close();
				}
			}

			// Don't apply gravity twice
			if (!moved && !jumped)
				gravity = Physic::gravity(&quinn, lvl.map);

			if (jumped) {
				const u8_t* keys = SDL_GetKeyboardState(nullptr);
				if (keys[SDL_SCANCODE_LEFT]) {
					quinn.position.x -= Physic::Force::JumpMove;
					quinn.rotationAngle -= 90;
				} else if (keys[SDL_SCANCODE_RIGHT]) {
					quinn.position.x += Physic::Force::JumpMove;
					quinn.rotationAngle += 90;
				}
			}

			Physic::jump(&quinn, lvl.map, jumped);

			u32_t win_w, win_h;
			wnd.fetchSize(&win_w, &win_h);

			if (quinn.position.x < 0 ||
				(quinn.position.y > 0 && 
				static_cast<u32_t>(quinn.position.y) > win_h))
			{
				std::cout << "You died!" << std::endl;
				SDL_Delay(1000);
				timer.start();
				quinn.position = quinnStartPos;
			} else if (quinn.position.x > 0 &&
				static_cast<u32_t>(quinn.position.x) > win_w)
			{
				if (!lvl.loadNext(rend)) {
					std::cout << "You've won!" << std::endl;
					break;
				}
			}

			rend->clear();
			lvl.map->renderOn(rend);
			rend->draw(quinn);
		}

		rend->present();
	}
}