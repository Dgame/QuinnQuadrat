#ifndef SDL_WINDOW_HPP
#define SDL_WINDOW_HPP

#include <vector>
#include "types.hpp"

struct SDL_Window;
using SDL_GLContext = void*; // TODO?

namespace sdl {
	struct Vector2i;
	struct Rect;

	class Drawable;
	class Surface;
	class Renderer;

	class Window {
	public:
		explicit Window(const char*, const Vector2i&, u32_t, u32_t, u32_t flags = 0);
		Window(const Window&) = delete;
		virtual ~Window();

		bool isValid() const {
			return _isValid;
		}

		void close() {
			_isValid = false;
		}

		Renderer* createRenderer(u32_t, i16_t driver_index = -1);

		void display() const;

		void blit(Surface*, Rect*, const Rect* src = nullptr) const;

		void draw(const Drawable&) const;

		void setTitle(const char*) const;
		const char* getTitle() const;

		void setSize(u32_t w, u32_t h) const;
		void fetchSize(u32_t* w, u32_t* h) const;

		u32_t width() const;
		u32_t height() const;

		void setPosition(u32_t, u32_t) const;
		void setPosition(const Vector2i&) const;
		Vector2i getPosition() const;

		u32_t getID() const;

		i32_t getDisplayIndex() const;
		Rect getDisplayBounds() const;

		void show() const;
		void hide() const;
		void focus() const;
		void restore() const;
		void minimize() const;
		void maximize() const;

		void setBorder(bool) const;
		void setIcon(const Surface&) const;

		u32_t getFlags() const;

		void setFullscreen(u32_t) const;

	private:
		bool _isValid;
		static u16_t _wnd_count;

		SDL_Window* _wnd;
		SDL_GLContext _gl_context;

		std::vector<Renderer*> _renderer;
	};
}

#endif