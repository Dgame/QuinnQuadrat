#include "WindowSprite.hpp"

#include <cmath>
#include <limits>

#include "Texture.hpp"
#include "Surface.hpp"
#include "Renderer.hpp"
#include "Window.hpp"
#include "Rect.hpp"

namespace sdl {
    WindowSprite::WindowSprite(Surface& srfc) : _srfc(&srfc) {
        
    }

    WindowSprite::WindowSprite(Surface& srfc, const Vector2i& pos) : Sprite(pos), _srfc(&srfc) {
        
    }

    Rect WindowSprite::getClipRect() const {
        u32_t w = 0, h = 0;

        if (this->sourceRect.isEmpty()) {
            w = _srfc->width();
            h = _srfc->height();
        } else {
            w = this->sourceRect.width;
            h = this->sourceRect.height;
        }

        return Rect(this->position.x, this->position.y, w, h);
    }

    void WindowSprite::renderOn(const Window* wnd) const {
        if (wnd && _srfc) {
            Rect dst = this->getClipRect();
            const Rect* p_src = this->sourceRect.isEmpty() ? nullptr : &this->sourceRect;

            wnd->blit(_srfc, &dst, p_src);
        }
    }
}