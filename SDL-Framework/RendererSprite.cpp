#include "RendererSprite.hpp"

#include <cmath>
#include <limits>

#include "Texture.hpp"
#include "Renderer.hpp"

namespace sdl {
	RendererSprite::RendererSprite(Texture* tex) : _tex(tex) {
		
	}

	RendererSprite::RendererSprite(Texture* tex, const Vector2i& pos) : Sprite(pos), _tex(tex) {

	}

	Rect RendererSprite::getClipRect() const {
		u32_t w = 0, h = 0;

		if (this->sourceRect.isEmpty()) {
			if (_tex)
				_tex->query(&w, &h);
		} else {
			w = this->sourceRect.width;
			h = this->sourceRect.height;
		}

		return Rect(this->position.x, this->position.y, w, h);
	}

	void RendererSprite::renderOn(const Renderer* rend) const {
		if (rend && _tex) {
			const Rect dst = this->getClipRect();
			const Rect* p_src = this->sourceRect.isEmpty() ? nullptr : &this->sourceRect;

			auto feq = [](f64_t a, f64_t b) {
				return std::fabs(a - b) < std::numeric_limits<f64_t>::epsilon();
			};

			if (!feq(this->rotationAngle, 0)) {
				rend->copy(_tex, &dst, this->rotationAngle, p_src);
			} else
				rend->copy(_tex, &dst, p_src);
		}
	}
}