#include "TileMap.hpp"
#include "SDL-Framework/Renderer.hpp"
#include "SDL-Framework/Window.hpp"
#include "SDL-Framework/Surface.hpp"
#include "pugixml/src/pugixml.hpp"
#include "Tile.hpp"

#include <iostream>
#include <sstream>
#include <cmath>

TileMap::TileMap(sdl::Renderer* rend, const std::string& filename) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(filename.c_str());
    // std::cout << filename << std::endl;

    if (result) {
        pugi::xml_node map_node = doc.child("map");
        _width = map_node.attribute("width").as_int();
        _height = map_node.attribute("height").as_int();

        pugi::xml_node image_node = map_node.child("tileset").child("image");
        const char* source = image_node.attribute("source").value();
        const std::string tileset_file = "media/" + std::string(source).substr(3);
        // std::cout << tileset_file << std::endl;
        _tex = sdl::Surface(tileset_file.c_str()).asTextureOf(rend);

        sdl::Vector2i pos;

        pugi::xml_node data = map_node.child("layer").child("data");
        for (pugi::xml_node_iterator it = data.begin(); it != data.end(); ++it) {
            // Layer
            for (pugi::xml_attribute_iterator ait = it->attributes_begin(); ait != it->attributes_end(); ++ait) {
                std::stringstream buf;
                buf << ait->value();
                u16_t index;
                buf >> index;
                
                if (index != 0)
                    _tiles.push_back(new Tile(index, _tex, pos));

                pos.x++;
                if (pos.x >= _width) {
                    pos.x = 0;
                    pos.y++;
                }
            }
        }
    } else
        std::cerr << "Could not load map " << filename << std::endl;
}


TileMap::~TileMap() {
    for (Tile* tile : _tiles) {
        delete tile;
    }
}

Tile* TileMap::getTileAt(const sdl::Vector2i& pos, sdl::Edge edge) const {
    for (Tile* tile : _tiles) {
        if (tile->getClipRect().getEdgePosition(edge) == pos)
            return tile;
    }

    return nullptr;
}

void TileMap::renderOn(const sdl::Renderer* rend) const {
    if (!rend)
        return;

    for (const Tile* tile : _tiles) {
        rend->draw(*tile);
    }
}