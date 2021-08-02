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
void Graph::addEdge(int node1, int node2) {
    if (node1 >= getNumberOfNode() || node2 >= getNumberOfNode()) {
        std::cerr << "idiot add nodes that doesnt exist. Try something smaller than the capacity." << std::endl;
        return;
    } else if (node1 == node2) {
        std::cerr << "node1 and node2 are both equal to: " << node1 << std::endl;
        return;
    } else {
        Node newNode1(node1);
        Node newNode2(node2);
        if (std::count(graph[node1].begin(), graph[node1].end(), node2)) {
            std::cerr << "Node " << node1 << " is already connected to node " << node2 << std::endl;
        }
        else if (std::count(graph[node2].begin(), graph[node2].end(), node1)) {
            std::cerr << "Node " << node2 << " is already connected to node " << node1 << std::endl;
        } else {
            graph[node1].emplace_after(graph[node1].begin(), newNode2);
            graph[node2].emplace_after(graph[node2].begin(), newNode1);
            std::cout << "is connecting node " << node1 << " and node " << node2 << std::endl;
            addToColoredEdge(newNode1, newNode2);
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
    /*int width = 50;
    int height = 30;*/

    sf::RectangleShape rectangle(sf::Vector2f(width, height));

    //why cant setPosition(node1.getShape().getPosition())????
    rectangle.setPosition(sf::Vector2f(node1.getXCoord() * Node::SIZE_CELL + Node::SIZE_BORDER,
                                       node1.getYCoord() * Node::SIZE_CELL + Node::SIZE_BORDER));

//    rectangle.setPosition(node1.getShape().getPosition());
    rectangle.setFillColor(color);
//    hmmm how to change this shit color not by magic color var
//    rectangle.setOutlineColor(sf::Color::Red);
//    rectangle.setOutlineThickness(Node::SIZE_BORDER);

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

/**
 * Only return the neighbor.
 * Omit the node standing in the front
 * @param node
 * @return
 */
std::vector<int> Graph::getNeighborNodes(int node) {
    std::vector<int>output;
    for (Node &n : graph[node]) {
        if (n == node) {
            continue;
        }
        output.emplace_back(n.getData());
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










