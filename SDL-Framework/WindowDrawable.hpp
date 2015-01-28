#ifndef SDL_WINDOW_DRAWABLE_HPP
#define SDL_WINDOW_DRAWABLE_HPP

namespace sdl {
    class Window;
    
    struct WindowDrawable {
        virtual ~WindowDrawable() { }

        virtual void renderOn(const Window*) const = 0;
    };
}

#endif