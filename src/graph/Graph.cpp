#include "Graph.h"
#include <vector>

// Constructors
Node::Node() : posn{0,0}, radius(20.0), label_angle(0.0), color(RED), i(-1), val(-1), displayVal(0) {}
Node::Node(Vector2 p, double r, Color c, int j)
        : posn(p), radius(r), label_angle(PI/4.0), color(c),
          i(j), val(0), displayVal(0) {}

Edge::Edge() : from(-1), to(-1), weight(0) {}
Edge::Edge(int u, int v) : from(u), to(v), weight(0) {}


/**
 * @brief Add a node to the graph
 * 
 * @param position The position of the node as a Vector2
 * @param radius The radius of the node
 * @return The id of the node that was just added
 */
int Graph::addNode(Vector2 position, float radius, Color color) {
    nodes[node_cid] = Node(position, radius, color, node_cid);
    return node_cid++;
}

/**
 * @brief Remove a node from the graph
 */
void Graph::deleteNode(int u) {
    // Delete all edges relating to u
    std::vector<int> to_delete;
    for(auto& [edge_id, edge] : edges) {
        if(edge.from == u or edge.to == u) {
            to_delete.push_back(edge_id);
        }
    }

    for(int e : to_delete) {
        edges.erase(e);
    }

    nodes.erase(u);
}

/**
 * @brief Add an edge to the graph.
 * 
 * @param u The beginning node index of the edge
 * @param v The ending node index of the edge
 * @return The id of the edge that was just added
 */
int Graph::addEdge(int u, int v) {
    if(u == v) return -1;

    edges[edge_cid] = Edge(u,v);
    return edge_cid++;
}

/**
 * @brief Delete an edge from the graph
 * 
 * @param e The index of the edge to be deleted
 */
void Graph::deleteEdge(int e) {
    edges.erase(e);
}

/**
 * @brief Get the node hovered by the mouse
 * 
 * @return The index of the node hovered by the mouse, or -1 if there is none
 */
int Graph::getHoveredNode(Vector2 mouse) const {
    for(const auto& [i, node] : nodes) {
        if(CheckCollisionPointCircle(mouse, node.posn, node.radius)) {
            return i;
        }
    }
    return -1;
}


/**
 * @brief Rotate the index label of a node
 * 
 * @param ang The angle (in radians) to rotate the label
 */
void Node::rotateLabel(double ang) {
    this->label_angle += ang;
    if(this->label_angle >= 2*PI) this->label_angle -= 2*PI;
    if(this->label_angle < 0) this->label_angle += 2*PI;
}