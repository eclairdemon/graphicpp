#include <raylib.h>
#include <iostream>
#include <vector>
#include <unordered_map>

#include "graph/Graph.h"
#include "rendering/Renderer.h"
#include "input/InputManager.h"
#include "config/Config.h"

int main() {
    int HEIGHT = 600;
    int WIDTH = 800;

    SetConfigFlags(FLAG_MSAA_4X_HINT); 
    InitWindow(WIDTH, HEIGHT, "graphic++");
    SetTargetFPS(60);

    Config conf;
    loadConfig(conf, "config/config.json");

    Graph graph;
    AppState curr_state = IDLE;
    int curr_node = -1;

    while(!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();
        double mouse_wheel = GetMouseWheelMove();

        int hovered_node = graph.getHoveredNode(mouse);

        if(mouse_wheel and hovered_node != -1) {
            graph.nodes[hovered_node].rotateLabel(mouse_wheel/3);
        }

        // State machine
        InputManager input;

        if(curr_state == IDLE) {
            if(hovered_node == -1) {
                if(input.isActionPressed(Action::CREATE_NODE)) {
                    // Make new node
                    curr_node = graph.addNode(mouse, 20.0, LIGHTGRAY);
                    curr_state = DRAWING_EDGE;
                }
            } else {
                curr_node = hovered_node;
                if(input.isActionPressed(Action::START_EDGE)) {
                    // Draw edge from current node
                    curr_state = DRAWING_EDGE;
                }

                if(input.isActionPressed(Action::DRAG_NODE)) {
                    // Drag current node
                    curr_state = DRAGGING_NODE;
                }

                if(input.isActionPressed(Action::DELETE_NODE)) {
                    // Delete node
                    graph.deleteNode(curr_node);
                }
            }
        }

        else if(curr_state == DRAGGING_NODE) {
            if(input.isActionReleased(Action::DRAG_NODE)) {
                curr_state = IDLE;
                curr_node = -1;
            } else {
                graph.nodes[curr_node].posn = mouse;
            }
        }


        else if(curr_state == DRAWING_EDGE) {
            if(input.isActionReleased(Action::START_EDGE)) {
                if(hovered_node != -1 and hovered_node != curr_node) {
                    graph.addEdge(curr_node, hovered_node);
                }

                curr_state = IDLE;
                curr_node = -1;
            }
        }

        DrawGraph(graph, curr_state, hovered_node, curr_node, mouse, conf);
    }

    unloadConfig(conf);
    CloseWindow();
    return 0;
}