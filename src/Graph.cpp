//
// Created by tieu on 7/28/2021.
//

#include <iostream>
#include <algorithm>
#include "Graph.hpp"


Graph::Graph(int numberOfNode, sf::Color color) : numberOfNode(numberOfNode), color(color) {
    for (int i = 0; i < numberOfNode; i++) {
        graph.emplace_back(std::forward_list<Node>());
        graph[i].emplace_front(Node(i));
    }
}

Graph::~Graph() {
}

void Graph::printGraph() {
    for (int i = 0; i < getNumberOfNode(); i++) {
//        std::cout << i << ": ";
        for (Node &n : graph[i]) {
            std::cout << n.getData() << " ";
        }
        std::cout << std::endl;
    }
}

/** Clear the adjacency list.
 */
void Graph::clearGraph() {
    for (int i = 0; i < numberOfNode; i++) {
        graph[i].clear();
    }
}


/**
 * Add two nodes to each other's adjacency list
 * @param node1
 * @param node2
 * Add to the second because its easier than add to last
 * if anything related to neighbor list traversal, change here to insert last
 */
void Graph::addEdge(Node node1, Node node2) {
    int data1 = node1.getData();
    int data2 = node2.getData();
    if (data1 >= getNumberOfNode() || data2 >= getNumberOfNode()) {
        std::cout << "idiot add nodes that doesnt exist. Try something smaller than the capacity." << std::endl;
        return;
    } else if (data1 == data2) {
        std::cout << "node1 and node2 are both equal to: " << data1 << std::endl;
        return;
    } else {
        if (std::count(graph[data1].begin(), graph[data1].end(), node2)) {
            std::cout << "Node " << data1 << " is already connected to node " << data2 << std::endl;
        } // du sao cung ko vao else if
        else if (std::count(graph[data2].begin(), graph[data2].end(), node1)) {
            std::cout << "Node " << data2 << " is already connected to node " << data1 << std::endl;
        } else {
            graph[data1].emplace_after(graph[data1].begin(), node2);
            graph[data2].emplace_after(graph[data2].begin(), node1);
            std::cout << "is connecting node " << data1 << " and node " << data2 << std::endl;
            addToColoredEdge(node1, node2);
        }
    }
}

//arrange node to draw from left to right, node1 < node2
void Graph::addToColoredEdge(Node node1, Node node2) {
    if (node1.getData() > node2.getData()) {
        Node tmp = node1;
        node1 = node2;
        node2 = tmp;
    }
    int width = (node2.getXCoord() + 1 - node1.getXCoord()) * Node::SIZE_CELL - 2 * Node::SIZE_BORDER;
    int height = (node2.getYCoord() + 1 - node1.getYCoord()) * Node::SIZE_CELL - 2 * Node::SIZE_BORDER;

    sf::RectangleShape rectangle(sf::Vector2f(width, height));

    //why cant setPosition(node1.getShape().getPosition())????
    rectangle.setPosition(sf::Vector2f(node1.getXCoord() * Node::SIZE_CELL + Node::SIZE_BORDER,
                                       node1.getYCoord() * Node::SIZE_CELL + Node::SIZE_BORDER));

    rectangle.setFillColor(color);

    coloredEdge.emplace_back(rectangle);
}


/**
 * Calculate the distance between two nodes.
 * On valid if on the same row or column (maybe it doesnt happen)
 * if doesnt assign coordination to both -> return 1 to help dijkstra
 * @param node1
 * @param node2
 * @return 1 or distance or another value implying they are not on the same col or row
 */
int Graph::getDistance(Node node1, Node node2) {
//    Node n1 = graph[node1].front();
//    Node n2 = graph[node2].front();

//    hope that x undefined -> y undefined
//wtf is this nhi??
    if (node1.getXCoord() == Node::UNDEFINED || node2.getXCoord() == Node::UNDEFINED) {
        return 1;
    }
    //if on the same row or column
    if (node1.getXCoord() == node2.getXCoord() || node1.getYCoord() == node2.getYCoord()) {
        return abs(node1.getXCoord() - node2.getXCoord()) + abs(node1.getYCoord() - node2.getYCoord());
    }
    //a temporary value because couldn't think of anything better
    return Node::UNDEFINED;
}

/**
 * Only return the neighbor.
 * Omit the node standing in the front
 * @param node
 * @return
 */
std::vector<Node> Graph::getNeighborNodes(Node node) {
    std::vector<Node>output;
    for (Node &n : graph[node.getData()]) {
        // :)
        if (n == node) {
            continue;
        }
        output.emplace_back(n);
    }

    return output;
}

int Graph::getNumberOfNode() const {
    return numberOfNode;
}


void Graph::draw(sf::RenderTarget &target, sf::RenderStates state) const {
    for (int i = 0; i < coloredEdge.size(); i++) {
//        std::cout << "is drawing edge " << i << std::endl;
        target.draw(coloredEdge[i]);
    }
}










