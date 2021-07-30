//
// Created by tieu on 7/28/2021.
//

#include <iostream>
#include "Graph.hpp"


Graph::Graph(int numberOfNode) : numberOfNode(numberOfNode) {
    for (int i = 0; i < numberOfNode; i++) {
        graph.emplace_back(std::forward_list<Node>());
        graph[i].emplace_front(Node(i));
    }
}

Graph::~Graph() {
}

void Graph::printGraph() {
    for (int i = 0; i < getNumberOfNode(); i++) {
        std::cout << i << ": ";
        for (Node &n : graph[i]) {
            std::cout << n.getData() << " ";
        }
        std::cout << std::endl;
    }
}

/**
 * Add two nodes to each other's adjacency list
 * @param node1
 * @param node2
 * Add to the second because its easier than add to last
 * if anything related to neighbor list traversal, change here to insert last
 */
void Graph::addEdge(int node1, int node2) {
    if (node1 >= getNumberOfNode() || node2 >= getNumberOfNode()) {
        std::cerr << "idiot add nodes that doesnt exist. Try something smaller than the capacity.";
        return;
    }
    Node newNode1(node1);
    Node newNode2(node2);
    graph[node1].emplace_after(graph[node1].begin(), newNode2);
    graph[node2].emplace_after(graph[node2].begin(), newNode1);

//    in case i'm an idiot and connect two already-connected nodes
    graph[node1].unique();
    graph[node2].unique();

}

/**
 * Calculate the distance between two nodes.
 * On valid if on the same row or column (maybe it doesnt happen)
 * if doesnt assign coordination to both -> return 1 to help dijkstra
 * @param node1
 * @param node2
 * @return 1 or distance or another value implying they are not on the same col or row
 */
int Graph::getDistance(int node1, int node2) {
    Node n1 = graph[node1].front();
    Node n2 = graph[node2].front();

//    hope that x undefined -> y undefined
    if (n1.getXCoord() == Node::UNDEFINED || n2.getXCoord() == Node::UNDEFINED) {
        return 1;
    }
    //if on the same row or column
    if (n1.getXCoord() == n2.getXCoord() || n1.getYCoord() == n2.getYCoord()) {
        return abs(n1.getXCoord() - n2.getXCoord()) + abs(n1.getYCoord() - n2.getYCoord());
    }
    //a temporary value because couldn't think of anything better
    return Node::UNDEFINED;
}

std::vector<int> Graph::getNeighborNodes(int node) {

    return std::vector<int>();
}

int Graph::getNumberOfNode() const {
    return numberOfNode;
}






