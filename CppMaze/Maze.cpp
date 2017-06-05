
#include <cstdint>
#include <cstddef>
#include <vector>
#include <iostream>

#include "Maze.h"

using namespace std;


Maze::Node::Node(int id_, int x_pos_, int y_pos_)
{
    id = id_;
    x_pos = x_pos_;
    y_pos = y_pos_;
}


Maze::Arc::Arc(int id_, int cost_, int connected_node_ids_[2])
{
    id = id_;
    cost = cost_;
    for (int i = 0; i < 2; ++i)
    {
        connected_node_ids[i] = connected_node_ids_[i];
    }
}


Maze::Maze(string map_file_name)
{
    map = Map(map_file_name);
}


int Maze::createNodesAndArcs()
{
    // Create the nodes and the arcs
    // Put a node at every intersection
    // How to find intersections?
    // Not a corridor, that is not just walls to the left and right,
    // or just up and down

    int next_node_id = 1;
    int next_arc_id = 1;
    (void) next_arc_id;

    for (size_t r = 0; r < map.map_height; ++r)
    {
        for (size_t c = 0; c < map.map_width; ++c)
        {
            if (r == 0)
            {
                // First row, find enterence
                if (atPath(c, r))
                {
                    Node node(next_node_id, c, r);
                    nodes.push_back(node);
                    ++next_node_id;
                }
                else
                {
                    continue;
                }
            }
            else if (r == map.map_height - 1)
            {
                // Last row, find exit
                if (atPath(c, r))
                {
                    Node node(next_node_id, c, r);
                    addAllConnections(&node);
                    nodes.push_back(node);
                    ++next_node_id;
                }
                else
                {
                    continue;
                }
            }
            else if (atIntersection(c, r))
            {
                // At intersection
                Node node(next_node_id, c, r);
                addAllConnections(&node);
                nodes.push_back(node);
                ++next_node_id;
            }
        }
    }

    return 0;
}

bool Maze::atPath(size_t x, size_t y)
{
    return map.map_data.at(y*map.map_height + x) == PATH;
}

bool Maze::atIntersection(size_t x, size_t y)
{
    if (atPath(x,y))
    {
        // Intersection if more than two adjacent paths or
        // if only one adjacent path, or if not corridor

        // paths [N, E, S, W]
        bool paths[4] = {atPath(x,y-1), atPath(x+1,y), atPath(x,y+1), atPath(x-1,y)};
        int counter = 0;
        for (size_t i = 0; i < 4; ++i)
        {
            if (paths[i])
            {
                ++counter;
            }
        }

        if (counter == 1)
        {
            // At dead end
            return true;
        }
        else if (counter > 2)
        {
            // Three-way or four-way
            return true;
        }
        else if ((paths[0] && paths[1])
                || (paths[1] && paths[2])
                || (paths[2] && paths[3])
                || (paths[3] && paths[0]))
        {
            // In a turn
            return true;
        }
        else
        {
            // Probably in a corridor
            return false;
        }
    }

    return false;
}

void Maze::addAboveConnection(Node* p_node)
{
    // Only search for connections adove the node
    (void) p_node;
}


void Maze::addBelowConnection(Node* p_node)
{
    (void) p_node;
}

void Maze::addLeftConnection(Node* p_node)
{
    (void) p_node;
}

void Maze::addRightConnection(Node* p_node)
{
    (void) p_node;
}

void Maze::addAllConnections(Node* p_node)
{
    // TODO: Write function
    if (p_node->x_pos == 0)
    {
        // First row, don't do anything
        return;
    }
    else if (p_node->x_pos == (signed) map.map_height-1)
    {
        // Last row, only search above
        addAboveConnection(p_node);
        return;
    }
    else if (p_node->x_pos > 0 && p_node->x_pos < (signed) map.map_height-1)
    {
        // All directions
        addAboveConnection(p_node);
        addBelowConnection(p_node);
        addLeftConnection(p_node);
        addRightConnection(p_node);
        return;
    }
    else
    {
        // Something has gone wrong!
        cerr << "Node outside of maze" << endl;
        return;
    }
}
