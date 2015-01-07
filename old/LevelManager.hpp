#ifndef SDL_LEVEL_MANAGER
#define SDL_LEVEL_MANAGER

#include "Framework/types.hpp"
#include <vector>

namespace sdl {
	class Renderer;
}

class Level;

class LevelManager {
public:
	LevelManager(sdl::Renderer*);
	virtual ~LevelManager();

	void load(u16_t lvl_nr) {
		if (lvl_nr < _lvls.size()) {
			_cur_lvl_nr = lvl_nr;
			_cur_lvl = _lvls[lvl_nr];
		} else {
			_cur_lvl_nr = -1;
			_cur_lvl = nullptr;
		}
	}

	Level* getCurrentLevel() const {
		return _cur_lvl;
	}

	i16_t getCurrentLevelNr() const {
		return _cur_lvl_nr;
	}

private:
	Level* _createNextLevel();

protected:
	std::vector<Level*> _lvls;

	i16_t _cur_lvl_nr = -1;
	Level* _cur_lvl = nullptr;
};

#endif