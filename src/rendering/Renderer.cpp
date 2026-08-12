#include <string>
#include <cmath>

#include "Renderer.h"

void DrawGraph(Graph graph, AppState state, int hovered_node, int active_node,
               Vector2 mouse, const Config& conf
            ) {
    
    BeginDrawing();
    ClearBackground(RAYWHITE);

    for(auto &[edge_id, edge] : graph.edges) {
        DrawLineEx(graph.nodes[edge.from].posn, graph.nodes[edge.to].posn,
                   conf.edge_thick, BLACK);
    }

    if(state == DRAWING_EDGE) {
        DrawLineEx(graph.nodes[active_node].posn, mouse, conf.edge_thick, LIGHTGRAY);
    }

    double r = conf.node_r;
    for(auto &[node_id, u] : graph.nodes) {
        double x = u.posn.x, y = u.posn.y;
        Color c = (node_id == hovered_node) ? GRAY : u.color;
        
        // Draw node proper
        DrawCircleV(u.posn, r, c);
        DrawRing(u.posn, r - conf.node_thick, r, 0.0f, 360.0f, 0, BLACK);

        // Figure out where to put the text
        double label_x = x + (r + 10.0) * cos(u.label_angle) - conf.font_size / 4.0;
        double label_y = y - (r + 10.0) * sin(u.label_angle) - conf.font_size / 2.0;
        

        DrawTextEx(conf.font, std::to_string(u.i).c_str(),
            (Vector2){(float)label_x, (float)label_y}, 24.0, 2, BLACK);
    }

    EndDrawing();
}