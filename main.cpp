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

const sdl::Vector2i StartPos(96, -96);
const sdl::Color SkyBlue(128, 189, 254);

void doRespawn(sdl::Renderer*, Entity&, Level*);

int main() {
    // Window
    sdl::Window wnd("Test-App", sdl::Vector2i(100, 100), Physic::WorldWidth, Physic::WorldHeight);
    sdl::Renderer* rend = wnd.createRenderer(SDL_RENDERER_ACCELERATED);
    rend->setDrawColor(SkyBlue);

    // Level
    LevelManager lvlm;
    Level* lvl = lvlm.loadNext(rend);

    if (!lvl) {
        std::cerr << "Could not load first level" << std::endl;
        return 0;
    }

    std::cout << sizeof(sdl::RendererSprite) << ':' << sizeof(sdl::WindowSprite) << ':' << sizeof(Entity) << std::endl;

    // Sprites

    // Quinn
    sdl::Texture* quinn_tex = sdl::Surface("media/Quinn-Quadrat.png").asTextureOf(rend);
    Entity quinn(new sdl::RendererSprite(quinn_tex, StartPos));

    // Timer
    sdl::Timer timer;
    timer.start();

    // FPS Timer
    sdl::Timer fpsTimer;
    fpsTimer.start();

    u32_t fps = 0;
    bool reversedGravity = false;

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

            if (!quinn.isMoving())
                Physic::gravityEffect(quinn, *lvl->map, reversedGravity);

            while (sdl::PollEvent(&event)) {
                if (event.type == SDL_KEYDOWN) {
                    switch (event.key.key) {
                        case SDLK_ESCAPE:
                            wnd.close();
                        break;

                        case SDLK_LEFT:
                            quinn.move(Direction::Left);
                        break;

                        case SDLK_RIGHT:
                            quinn.move(Direction::Right);
                        break;

                        case SDLK_UP:
                            reversedGravity = !reversedGravity;
                        break;

                        case SDLK_SPACE:
                            std::cout << '(' << quinn.sprite->position.x << ':' << quinn.sprite->position.y << ')' << std::endl;
                    }
                } else if (event.type == SDL_QUIT) {
                    wnd.close();
                }
            }
            
            if (!lvl->freezed)
                quinn.roll();

            if (Physic::outOfBounds(quinn)) {
                std::cout << "You died!" << std::endl;
                quinn.state = State::Dead;
            }

            if (quinn.isDead()) {
                if (!Physic::dropEffect(quinn)) {
                    doRespawn(rend, quinn, lvl);

                    timer.start();
                    reversedGravity = false;
                }
            }

            const State stateBefore = quinn.state;

            if (quinn.isAlive() && !lvl->freezed) {
                lvl->interaction(quinn);

                if (stateBefore != quinn.state) {
                    if (quinn.isDead()) {
                        quinn.sprite->rotationAngle = 180;
                        quinn.moving = 0;
                    } else if (quinn.isHurt()) {
                        // TODO: 
                    }
                }
            }

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

void doRespawn(sdl::Renderer* rend, Entity& entity, Level* lvl) {
    rend->setDrawColor(sdl::Color::Black);
    rend->clear();
    rend->present();

    SDL_Delay(1500);

    rend->setDrawColor(SkyBlue);

    entity.restore();

    if (lvl)
        lvl->restore();
}