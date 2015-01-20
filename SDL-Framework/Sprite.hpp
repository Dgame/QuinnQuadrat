#ifndef SDL_SPRITE_HPP
#define SDL_SPRITE_HPP

#include "Vector2.hpp"
#include "Rect.hpp"
#include "Drawable.hpp"

namespace sdl {
	class Texture;
	class Surface;

	class Sprite : public Drawable {
	public:
		explicit Sprite(Texture*);
		explicit Sprite(Texture*, const Vector2i&);

		explicit Sprite(Surface&);
		explicit Sprite(Surface&, const Vector2i&);

		virtual ~Sprite() { }

		Surface* setImage(Surface&);
		Texture* setImage(Texture*);

		Surface* getSurface() const {
			return _srfc;
		}

		Texture* getTexture() const {
			return _tex;
		}

		Rect getClipRect() const;

		virtual void renderOn(const Renderer*) const override;
		virtual void renderOn(const Window*) const override;

	private:
		Texture* _tex = nullptr;
		Surface* _srfc = nullptr;

	public:
		Vector2i position;
		Vector2i center;

		f64_t rotationAngle = 0;
		u8_t flipMode = 0;

		Rect sourceRect;
	};
}

#endif