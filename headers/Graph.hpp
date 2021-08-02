//
// Created by tieu on 7/28/2021.
//

#ifndef DSA_GRAPH_HPP
#define DSA_GRAPH_HPP


#include <vector>
#include <forward_list>
#include "Node.hpp"

/**
 ** Maintaining mazeGraph by a adjacency list.
 * implemented by a vector of linked list
 * Adjacency list:
 * [0]: Node(0) -> neighbor -> nodes -> in -> reverse -> inserted -> order
 * [1]: Node(1) -> neighbor -> nodes -> in -> reverse -> inserted -> order
 * [2]: Node(2) -> neighbor -> nodes -> in -> reverse -> inserted -> order
 */
class Graph {
private:
//    adjacency list
    std::vector<std::forward_list<Node>> graph;
    
    int numberOfNode;

public:
    //van se maintain numberOfNode by size of the screen
    Graph(int numberOfNode);

    virtual ~Graph();

    void printGraph();

    void clearGraph();

    void addEdge(int node1, int node2);

    int getDistance(int node1, int node2);

    int getNumberOfNode() const;

    std::vector<int> getNeighborNodes(int node);

};


#endif //DSA_GRAPH_HPP
