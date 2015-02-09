#ifndef SDL_WINDOW_SPRITE_HPP
#define SDL_WINDOW_SPRITE_HPP

#include "WindowDrawable.hpp"
#include "Sprite.hpp"

namespace sdl {
    class Surface;

    class WindowSprite : public Sprite, public WindowDrawable {
    public:
        explicit WindowSprite(Surface&);
        explicit WindowSprite(Surface&, const Vector2i&);

        virtual ~WindowSprite() { }

        Surface* setSurface(Surface& new_srfc) {
            Surface* old_srfc = _srfc;
            _srfc = &new_srfc;

            return old_srfc;
        }

        Surface* getSurface() const {
            return _srfc;
        }

        virtual Rect getClipRect() const override;
        virtual void renderOn(const Window*) const override;

    private:
        Surface* _srfc = nullptr;
    };
}

#endif