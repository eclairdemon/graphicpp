#pragma once
#include <unordered_map>

#include "graph/Graph.h"
#include "input/Actions.h"
#include "config/Config.h"

void DrawGraph(Graph graph, AppState state, int hovered_node, int active_node,
               Vector2 mouse, const Config& conf
            );