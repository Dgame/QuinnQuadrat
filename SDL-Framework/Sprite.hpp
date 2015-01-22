#ifndef SDL_SPRITE_HPP
#define SDL_SPRITE_HPP

#include "Vector2.hpp"
#include "Rect.hpp"

namespace sdl {
	struct Sprite {
		Vector2i position;
		Rect sourceRect;

		Sprite() = default;
		explicit Sprite(const Vector2i&);
		virtual ~Sprite() { }

		virtual Rect getClipRect() const = 0;
	};
}

#endif