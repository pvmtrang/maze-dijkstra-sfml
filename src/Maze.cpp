//
// Created by tieu on 7/31/2021.
//

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include "Maze.hpp"

static const int WIDTH = 6;
static const int HEIGHT = 5;
//const int NUMBER_OF_CELL = WIDTH * HEIGHT;

//set value like this only work with 0
Maze::Maze() : mazeGraph(NUMBER_OF_CELL), weightedGraph(NUMBER_OF_CELL) {
    srand((int) time(0));

}

/**
 * Using prim to generate maze
 * @param fromNode
 */
void Maze::generateMaze(int fromNode) {
//    come back to this later. To generate maze more than once
//    mazeGraph.clearGraph();


    addedToGraphNode.emplace_back(Node(fromNode));
//    Node(fromNode).render(Painter::getWindow(), sf::Color::White);

    //while not all nodes are in mazeGraph
    while(addedToGraphNode.size() != NUMBER_OF_CELL) {
        //Choose a random node in mazeGraph
        Node randomNode = getRandomNode(addedToGraphNode);
        //Connect to a random neighbor node that is not in mazeGraph
        std::vector<Node> neighbors = getUnvisitedNeighborNode(randomNode);
        Node randomNeighbor = getRandomNode(neighbors);
        //if there's no unvisited neighbor nodes -> skip this one;
        if (randomNeighbor.getData() == Node::UNDEFINED) {
            continue;
        } else {
//this shit is so suspicious
            mazeGraph.addEdge(randomNode.getData(), randomNeighbor.getData());
            //Add that neighbor to mazeGraph
            addedToGraphNode.emplace_back(randomNeighbor);
        }
    }
    mazeGraph.printGraph();

}

/**
 * To choose a random node from a set.
 * No deletion or anything
 * Is used in generating maze
 * @param nodeSet: this set might be addedToGraphNode or getNeighborNode
 * @return a Node with data UNDEFINED when there's none to return, else return a random from nodeSet.
 */
// how about return a null node??
Node Maze::getRandomNode(std::vector<Node> nodeSet) {
    if (nodeSet.empty()) {
        return Node(Node::UNDEFINED);
    }
    unsigned int randomIndex = rand() % nodeSet.size();
    Node randomNode = nodeSet[randomIndex];

    return randomNode;
}

/**
 * Find all node that is a valid node and not added in mazeGraph next to the given node.
 * Is used in generating maze
 * @param n
 * @return the set of all qualified nodes
 */
std::vector<Node> Maze::getUnvisitedNeighborNode(Node n) {
    std::vector<Node> output;

    int upX = n.getXCoord();
    int upY = n.getYCoord() - 1;
    int downX = n.getXCoord();
    int downY = n.getYCoord() + 1;
    int leftX = n.getXCoord() - 1;
    int leftY = n.getYCoord();
    int rightX = n.getXCoord() + 1;
    int rightY = n.getYCoord();

    if (upY >= 0) {
        Node up(upY * WIDTH + upX);
        if (!isInGraph(up)) {
            output.emplace_back(up);
        }
    }
    if (downY < HEIGHT) {
        Node down(downY * WIDTH + downX);
        if (!isInGraph(down)) {
            output.emplace_back(down);
        }
    }
    if (leftX >= 0) {
        Node left(leftY * WIDTH + leftX);
        if (!isInGraph(left)) {
            output.emplace_back(left);
        }
    }
    if (rightX >= 0) {
        Node right(rightY * WIDTH + rightX);
        if (!isInGraph(right)) {
            output.emplace_back(right);
        }
    }

    return output;
}

/**
 * Check if a node n is already in mazeGraph.
 * A node in mazeGraph = a node in addedToGraphNode = a node has neighbor
 * @param n
 * @return if it's already added in mazeGraph
 */
bool Maze::isInGraph(Node n) {
    return std::count(addedToGraphNode.begin(), addedToGraphNode.end(), n);
}

Graph Maze::getMazeGraph() {
    return mazeGraph;
}

//Chua nghi den viec them start va end node vao kieu gi
//Or de mac dinh start la 0 va end la 29: 2 node nay luon qualified
void Maze::generateWeightedGraph() {
//1. find all possible qualified node
    std::vector<int> qualifiedNode;
    for (int i = 0; i < mazeGraph.getNumberOfNode(); i++) {
        if (isQualifiedForWeightedGraph(i)) {
            qualifiedNode.emplace_back(i);
        }
    }
//2. generate the weighted graph
//    weightedGraph = Graph(qualifiedNode.size());

    for (int iQualifiedNode : qualifiedNode) {
        //loop through it's neighbor
        for (int iNeighbor : mazeGraph.getNeighborNodes(iQualifiedNode)) {
            //if that neighbor is qualified -> create an edge for weighted graph
            if (isQualifiedForWeightedGraph(iNeighbor)) {
                weightedGraph.addEdge(iQualifiedNode, iNeighbor);
            } else {
            // dig depth into neighbor's neighbor until reach the first qualified node
                int nextQualified = findNextQualifiedNode(iNeighbor);
                weightedGraph.addEdge(iQualifiedNode, nextQualified);

            }
        }
    }

    weightedGraph.printGraph();
}

//this is like depth first search without backtracking
//take the first neighbor in the neighbor set
//and keep digging into that first neighbor's first neighbor
int Maze::findNextQualifiedNode(int node) {
    int firstNeighbor = mazeGraph.getNeighborNodes(node)[0];
    if (isQualifiedForWeightedGraph(firstNeighbor)) {
        return firstNeighbor;
    }
    return findNextQualifiedNode(firstNeighbor);
}

/**
 * A node addable to a weighted graph can be a dead-end, a turn or a junction, except for the start and end node.
 * Recognize by the number of neighbor node in mazegraph
 *  1 neighbor -> dead end
 *  2 neighbors: if in different col and row -> turn
 *  >2 neighbors: junction
 */
bool Maze::isQualifiedForWeightedGraph(int node) {
    std::vector<int> neighbor = mazeGraph.getNeighborNodes(node);
    switch (neighbor.size()) {
        case 0: {//might not happen. Forse
            return false;
        }
        case 1: {// 1 neighbor = a dead end
            return true;
        }
        case 2: {
            Node n1(neighbor[0]);
            Node n2(neighbor[1]);
            // 2 neighbor not on the same col or row aka a turn
            if (n1.getXCoord() == n2.getXCoord() || n1.getYCoord() == n2.getYCoord()) {
                return false;
            }
            return true;
        }
        default: // >2 neighbor aka a junction
            return true;
    }
}

Graph Maze::getWeightedGraph() {
//    generateWeightedGraph();
    return weightedGraph;
}









