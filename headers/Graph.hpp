//
// Created by tieu on 7/28/2021.
//

#ifndef DSA_GRAPH_HPP
#define DSA_GRAPH_HPP


#include <vector>

class Graph {
private:
//    adjacency matrix
    std::vector<std::vector<int>> weightedGraph;
    int numberOfNode;

public:
    static const int UNDEFINED = -1; //This is just the declaration, the def is in cpp

    Graph(int numberOfNode);

    virtual ~Graph();

    void printGraph();

    void addEdge(int node1, int node2, int weight);

    int getWeight(int node1, int node2);

    int getNumberOfNode() const;

    std::vector<int> getNeighborNodes(int node);

};


#endif //DSA_GRAPH_HPP
