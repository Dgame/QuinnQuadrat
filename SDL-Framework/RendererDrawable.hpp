#ifndef SDL_RENDERER_DRAWABLE_HPP
#define SDL_RENDERER_DRAWABLE_HPP

namespace sdl {
    class Renderer;

    struct RendererDrawable {
        virtual ~RendererDrawable() { }
        
        virtual void renderOn(const Renderer*) const = 0;
    };
}

#endif