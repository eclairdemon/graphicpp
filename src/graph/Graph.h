#pragma once
#include <raylib.h>
#include <unordered_map>

struct Node {
    Vector2 posn;
    double radius, label_angle;
    Color color;
    int i, val;
    bool displayVal;

    Node();
    Node(Vector2 p, double r, Color c, int j);
    
    void rotateLabel(double ang);
};

struct Edge {
    int from, to, weight;

    Edge();
    Edge(int u, int v);
};

class Graph {
private:
    int node_cid = 0;
    int edge_cid = 0;

public:
    std::unordered_map<int, Node> nodes;
    std::unordered_map<int, Edge> edges;

    int addNode(Vector2 position, float radius, Color color);
    void deleteNode(int u);

    int addEdge(int u, int v);
    void deleteEdge(int e);
    
    int getHoveredNode(Vector2 mouse) const;
};