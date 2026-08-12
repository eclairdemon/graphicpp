#include <iostream>
#include <fstream>

#include "config/Config.h"
#include "json.hpp"

// Magic
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Config, node_r, node_thick, edge_thick, font_size)

void loadConfig(Config& conf, const std::string &filepath) {
    std::ifstream file(filepath);
    if(file.is_open()) {
        try {
            nlohmann::json j;
            file >> j;
            conf = j.get<Config>();
        } catch(const nlohmann::json::exception& e) {
            std::cerr << "JSON Error: " << e.what() << std::endl;
        }
    }
}

void unloadConfig(Config& conf) {
    if(conf.font.texture.id != 0 and conf.font.texture.id != GetFontDefault().texture.id) {
        UnloadFont(conf.font);
    }
}