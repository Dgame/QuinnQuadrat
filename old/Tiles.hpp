#ifndef SDL_Tiles_HPP
#define SDL_Tiles_HPP

#include <vector>

#include "Framework/types.hpp"
#include "Framework/Drawable.hpp"

namespace sdl {
	struct Vector2i;

	class Texture;
	class Surface;
	class Sprite;
	class Renderer;
	class Window;
}

class Tiles : public sdl::Drawable {
public:
	Tiles() = default;
	Tiles(const Tiles&) = delete;
	virtual ~Tiles();

	void createTileAt(const sdl::Vector2i&, sdl::Texture*);
	void createTileAt(const sdl::Vector2i&, sdl::Surface&);
	void deleteTileAt(const sdl::Vector2i&);

	sdl::Sprite* releaseTileAt(const sdl::Vector2i&);
	sdl::Sprite* getTileAt(const sdl::Vector2i&, u32_t* index = nullptr);

	void move(u32_t, u32_t);
	void move(const sdl::Vector2i&);

	virtual void renderOn(const sdl::Renderer*) const override;
	virtual void renderOn(const sdl::Window*) const override;

private:
	std::vector<sdl::Sprite*> _tiles;
};


#endif