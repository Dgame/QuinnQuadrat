#include "Level.hpp"
#include "TileMap.hpp"

#include "SDL-Framework/Surface.hpp"
#include "Tile.hpp"

#include <iostream>
#include <sstream>
#include <fstream>

sdl::Texture* Level::GeoGauner = nullptr;
sdl::Texture* Level::SkyCloud = nullptr;

namespace {
    void initTextures(sdl::Renderer* rend) {
        Level::GeoGauner = sdl::Surface("media/Geo-Gauner.png").asTextureOf(rend);
        Level::SkyCloud = sdl::Surface("media/Cloud.png").asTextureOf(rend);
    }

    bool checkFile(const std::string& filename) {
        FILE* f = fopen(filename.c_str(), "rb");
        if (!f) {
            std::cerr << "No such file: " << filename << std::endl;
            return false;
        }
        fclose(f);

        return true;
    }
}

void Level::loadData(std::vector<LevelData>& data) {
    if (!this->map || this->lvlNr == 0)
        return;
    
    std::stringstream buf;
    buf << "media/lvl/Level_" << this->lvlNr << ".txt";

    const std::string filename = buf.str();
    checkFile(filename);

    std::ifstream input(filename);
    std::string line;

    while (std::getline(input, line)) {
        std::stringstream ss(line);
        LevelData lvl_data;

        ss >> lvl_data.position.x;
        ss.ignore();
        ss >> lvl_data.position.y;
        ss.ignore();
        ss >> lvl_data.type;

        lvl_data.position.x *= Tile::Size;
        lvl_data.position.y *= Tile::Size;

        data.push_back(lvl_data);
    }
}

Level::~Level() {
    delete this->map;
}

bool Level::build(sdl::Renderer* rend, u16_t nr) {
    if (!rend)
        return false;

    if (!GeoGauner)
        initTextures(rend);

    if (this->map)
        return true;

    this->lvlNr = nr;

    std::stringstream buf;
    buf << "media/lvl/Level_" << nr << ".tmx";

    const std::string filename = buf.str();
    checkFile(filename);

    this->map = new TileMap(rend, filename);

    return true;
}

void Level::renderOn(sdl::Renderer* rend) const {
    if (this->map)
        this->map->renderOn(rend);
}