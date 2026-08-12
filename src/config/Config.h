#pragma once
#include <string>
#include "raylib.h"

struct Config {
    double node_r = 20.0;
    double node_thick = 3.0;
    double edge_thick = 4.0;
    double font_size = 24.0;
    std::string font_path = "";

    Font font = {0};
};

void loadConfig(Config& conf, const std::string& filepath);
void unloadConfig(Config& conf);