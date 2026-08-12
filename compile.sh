#!/usr/bin/env bash

set -e

COMPILER="g++"
STD_FLAGS="-std=c++17 -Wall -Iinclude -Isrc"
SOURCES="./src/main.cpp ./src/rendering/Renderer.cpp ./src/graph/Graph.cpp"
OUTPUT="gcpp"

if command -v pkg-config >/dev/null 2>&1 && pkg-config --exists raylib; then
    RAYLIB_FLAGS=$(pkg-config --cflags --libs raylib)
else
    RAYLIB_FLAGS="-lraylib -lGL -lm -lpthread -ldl -lrt -lX11"
fi

$COMPILER $STD_FLAGS $SOURCES -o $OUTPUT $RAYLIB_FLAGS
echo "Compiled successfully."