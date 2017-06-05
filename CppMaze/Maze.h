#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <cstdint>
#include <cstddef>

#define WALL 0
#define PATH 1

class Maze
{
public:
    class Node
    {
    public:
        int id = 0;
        int connected_arc_ids[4] = {0,0,0,0};
        int x_pos = 0;
        int y_pos = 0;

        Node() = default;
        ~Node() = default;
        Node(Node const &) = default;
        Node(Node &&) = default;
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
        Arc(Arc const &) = default;
        Arc(Arc &&) = default;
        Arc(int id_, int cost_, int connected_node_ids_[2]);
    };

    std::vector<uint8_t> map;
    unsigned int map_width = 0;
    unsigned int map_height = 0;
    std::vector<Node> nodes;

    Node* p_start_node = nullptr;
    Node* p_end_node = nullptr;

    Maze() = default;
    ~Maze() = default;
    Maze(Maze const &) = default;
    Maze(Maze &&) = default;
    Maze(std::vector<uint8_t> map_, unsigned int map_width_, unsigned int map_height_);



private:
    bool atPath(size_t x, size_t y);
    bool atIntersection(size_t x, size_t y);
    int createNodesAndArcs();

    void addAllConnections(Node* p_node);
    void addAboveConnection(Node* p_node);
    void addBelowConnection(Node* p_node);
    void addLeftConnection(Node* p_node);
    void addRightConnection(Node* p_node);
};

#endif
