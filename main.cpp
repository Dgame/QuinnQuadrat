#include "SDL-Framework/Window.hpp"
#include "SDL-Framework/Renderer.hpp"
#include "SDL-Framework/Event.hpp"
#include "SDL-Framework/Color.hpp"
#include "SDL-Framework/WindowSprite.hpp"
#include "SDL-Framework/RendererSprite.hpp"
#include "SDL-Framework/Surface.hpp"
#include "SDL-Framework/Timer.hpp"

#undef main

#include "LevelManager.hpp"
#include "Level.hpp"
#include "TileMap.hpp"
#include "Tile.hpp"
#include "Physic.hpp"
#include "Entity.hpp"

#include <iostream>

const u16_t MaxFPS = 60;
const u16_t TicksPerFrame = 1000 / MaxFPS;

const sdl::Color skyBlue(128, 189, 254);

void doRespawn(sdl::Renderer*);

int main() {
    // Window
    sdl::Window wnd("Test-App", sdl::Vector2i(100, 100), 800, 480);
    sdl::Renderer* rend = wnd.createRenderer(SDL_RENDERER_ACCELERATED);
    rend->setDrawColor(skyBlue);

    // Level
    LevelManager lvlm;
    Level* lvl = lvlm.loadNext(rend);

    if (!lvl) {
        std::cerr << "Could not load first level" << std::endl;
        return 0;
    }

    // Sprites

    // Quinn
    sdl::Texture* quinn_tex = sdl::Surface("media/Quinn-Quadrat.png").asTextureOf(rend);
    sdl::Vector2i quinnStartPos(96, -96);
    Entity quinn(new sdl::RendererSprite(quinn_tex, quinnStartPos));

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
            // std::cout << "FPS: " << fps << std::endl;
            fps = 0;
        } else
            fps++;
        
        const u32_t frameTicks = timer.getTicks();
        if (frameTicks > TicksPerFrame) {
            timer.start();

            bool isFalling = false;

            if (quinn.jumping)
                Physic::jumpEffect(quinn, lvl->map);
            else if (!quinn.moving)
                isFalling = Physic::gravityEffect(quinn, lvl->map);

            while (sdl::PollEvent(&event)) {
                if (event.type == SDL_KEYDOWN) {
                    switch (event.key.key) {
                        case SDLK_ESCAPE:
                            wnd.close();
                        break;

                        case SDLK_LEFT:
                            if (!isFalling)
                                quinn.move(Direction::Left);
                        break;

                        case SDLK_RIGHT:
                            if (!isFalling)
                                quinn.move(Direction::Right);
                        break;

                        case SDLK_UP:
                            if (!isFalling)
                                quinn.jump();
                        break;
                    }
                } else if (event.type == SDL_QUIT) {
                    wnd.close();
                }
            }
            
            if (!isFalling)
                quinn.roll();
            else
                quinn.moving = 0;

            u32_t win_w, win_h;
            wnd.fetchSize(&win_w, &win_h);

            bool respawn = false;

            if (quinn.sprite->position.x < 0 ||
                (quinn.sprite->position.y > 0 && 
                static_cast<u32_t>(quinn.sprite->position.y) > win_h))
            {
                std::cout << "You died!" << std::endl;
                respawn = true;
            }

            if (respawn) {
                doRespawn(rend);

                timer.start();
                quinn.sprite->position = quinnStartPos;
                quinn.jumping = quinn.moving = quinn.sprite->rotationAngle = 0;
            }

            lvl->interaction(quinn);

            if (lvl->finished) {
                lvl = lvlm.loadNext(rend);
                if (!lvl) {
                    std::cout << "You've won!" << std::endl;
                    break;
                }
            }
            
            rend->clear();

            lvl->backgroundMotion();
            lvl->renderOn(rend);

            quinn.sprite->renderOn(rend);

        }

        rend->present();
    }
}

void doRespawn(sdl::Renderer* rend) {
    rend->setDrawColor(sdl::Color::Black);
    rend->clear();
    rend->present();

    SDL_Delay(1500);

    rend->setDrawColor(skyBlue);
}