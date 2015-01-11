#include "Sprite.hpp"

#include <cmath>
#include <limits>

#include "Texture.hpp"
#include "Surface.hpp"
#include "Renderer.hpp"
#include "Window.hpp"
#include "Rect.hpp"

namespace sdl {
	Sprite::Sprite(Texture* tex) : _tex(tex) {
		
	}

	Sprite::Sprite(Texture* tex, const Vector2i& pos) : _tex(tex), position(pos) {

	}

	Sprite::Sprite(Surface& srfc) : _srfc(&srfc) {
		
	}

	Sprite::Sprite(Surface& srfc, const Vector2i& pos) : _srfc(&srfc), position(pos) {

	}

	Surface* Sprite::setImage(Surface& srfc) {
		Surface* old = _srfc;
		_srfc = &srfc;

		return old;
	}

	Texture* Sprite::setImage(Texture* tex) {
		Texture* old = _tex;
		_tex = tex;

		return old;
	}

	Rect Sprite::getClipRect() const {
		u32_t w = 0, h = 0;

		if (this->sourceRect.isEmpty()) {
			if (_tex)
				_tex->query(&w, &h);
			else if (_srfc) {
				w = _srfc->width();
				h = _srfc->height();
			}
		} else {
			w = this->sourceRect.width;
			h = this->sourceRect.height;
		}

		return Rect(this->position.x, this->position.y, w, h);
	}

	void Sprite::renderOn(const Renderer* rend) const {
		if (rend && _tex) {
			const Rect dst = this->getClipRect();
			const Rect* p_src = this->sourceRect.isEmpty() ? nullptr : &this->sourceRect;

			auto feq = [](f64_t a, f64_t b) {
				return std::fabs(a - b) < std::numeric_limits<f64_t>::epsilon();
			};

			if (!feq(this->angle, 0)) {
				const Vector2i* p_center = this->center.isNull() ? nullptr : &this->center;
				rend->copy(_tex, &dst, this->angle, p_src, p_center, this->flipMode);
			} else
				rend->copy(_tex, &dst, p_src);
		}
	}

	void Sprite::renderOn(const Window* wnd) const {
		if (wnd && _srfc) {
			Rect dst = this->getClipRect();
			const Rect* p_src = this->sourceRect.isEmpty() ? nullptr : &this->sourceRect;

			wnd->blit(_srfc, &dst, p_src);
		}
	}
}