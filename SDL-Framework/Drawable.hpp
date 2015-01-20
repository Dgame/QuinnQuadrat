#ifndef SDL_DRAWABLE_HPP
#define SDL_DRAWABLE_HPP

namespace sdl {
	class Renderer;
	class Window;
	
	struct Drawable {
		virtual ~Drawable() { }
		
		virtual void renderOn(const Renderer*) const = 0;
		virtual void renderOn(const Window*) const = 0;
	};
}

#endif