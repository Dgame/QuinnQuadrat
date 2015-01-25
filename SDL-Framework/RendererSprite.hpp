#ifndef SDL_RENDERER_SPRITE_HPP
#define SDL_RENDERER_SPRITE_HPP

#include "RendererDrawable.hpp"
#include "Sprite.hpp"

namespace sdl {
	class Texture;

	class RendererSprite : public Sprite, public RendererDrawable {
	public:
		explicit RendererSprite(Texture*);
		explicit RendererSprite(Texture*, const Vector2i&);

		virtual ~RendererSprite() { }

		Texture* setTexture(Texture* new_tex) {
			Texture* old_tex = _tex;
			_tex = new_tex;

			return old_tex;
		}

		Texture* getTexture() const {
			return _tex;
		}

		virtual Rect getClipRect() const override;

		virtual void renderOn(const Renderer*) const override;
	private:
		Texture* _tex = nullptr;

	public:
		// Vector2i center;
		u8_t flipMode = 0;
		f64_t rotationAngle = 0;
	};
}

#endif