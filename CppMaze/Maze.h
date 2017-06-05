#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <cstdint>
#include <cstddef>
#include <string>

#include "Map.h"

#define WALL 0
#define PATH 1

class Maze
{
public:
    class Node
    {
    public:
        int id = 0;
        int connected_arc_ids[4] = {0,0,0,0}; // [N,E,S,W]
        int x_pos = 0;
        int y_pos = 0;

        Node() = default;
        ~Node() = default;
        Node(int id_, int x_pos_, int y_pos_);
    };


    class Arc
    {
    public:
        int id = 0;
        int cost = 0;
        int connected_node_ids[2] = {0,0};

        Arc() = default;
        ~Arc() = default;
        Arc(int id_, int cost_, int connected_node_ids_[2]);
    };

    Map map;
    std::vector<Node> nodes;
    std::vector<Arc> arcs;

    Node* p_start_node = nullptr;
    Node* p_end_node = nullptr;

    Maze() = default;
    ~Maze() = default;
    Maze(Maze const &) = default;
    Maze(Maze &&) = default;
    Maze(std::string map_file_name);



private:
    int next_node_id = 1;
    int next_arc_id = 1;

    bool atPath(int x, int y);
    bool atIntersection(int x, int y);
    int createNodesAndArcs();

    void addAllConnections(Node* p_node);
    void addAboveConnection(Node* p_node);
    void addBelowConnection(Node* p_node);
    void addLeftConnection(Node* p_node);
    void addRightConnection(Node* p_node);

    Node* getNodeAtXY(int x, int y);
};

#endif
