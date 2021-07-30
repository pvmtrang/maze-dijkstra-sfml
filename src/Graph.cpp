//
// Created by tieu on 7/28/2021.
//

#include <iostream>
#include "Graph.hpp"

const int Graph::UNDEFINED;     //this is the definition. *mindblow*

Graph::Graph(int numberOfNode) {
    this->numberOfNode = numberOfNode;

    for (int i = 0; i < numberOfNode; i++) {
        weightedGraph.push_back(std::vector<int>());
        for (int j = 0; j < numberOfNode; j++) {
            weightedGraph[i].push_back(UNDEFINED);
        }
    }
}

Graph::~Graph() {

}

void Graph::printGraph() {
    for (int i = 0; i < weightedGraph.size(); i++) {
        for (int j = 0; j < weightedGraph[i].size(); j++) {
            std::cout << weightedGraph[i][j] << " ";
        }
//        endle doesnt occupy memory, \n is a character -> 1 byte
        std::cout << std::endl;
    }
}

/**
 * Pretend that no one will assert an edge > width or height because i dont care.
 * @param node1
 * @param node2
 * @param weight: the edge weight
 */
void Graph::addEdge(int node1, int node2, int weight) {
    weightedGraph[node1][node2] = weight;
    weightedGraph[node2][node1] = weight;

}

int Graph::getWeight(int node1, int node2) {
    return weightedGraph[node1][node2];
}

std::vector<int> Graph::getNeighborNodes(int node) {
    std::vector<int> neighbor;
    for (int i = 0; i < weightedGraph[node].size(); i++) {
        if (weightedGraph[node][i] > UNDEFINED) {
            neighbor.push_back(i);
        }
    }
    return neighbor;
}

int Graph::getNumberOfNode() const {
    return numberOfNode;
}




