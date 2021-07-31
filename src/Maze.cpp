//
// Created by tieu on 7/31/2021.
//

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include "Maze.hpp"

const int WIDTH = 6;
const int HEIGHT = 5;
const int NUMBER_OF_CELL = WIDTH * HEIGHT;

//set value like this only work with 0
Maze::Maze() : cellStatus{IS_WALL}, graph(NUMBER_OF_CELL){
    srand((int) time(0));
// ??? does this work?   graph = Graph(NUMBER_OF_CELL);

}

/**
 * Using prim to generate maze
 * @param fromNode
 */
void Maze::generateMaze(int fromNode) {
//    come back to this later. To generate maze more than once
//    graph.clearGraph();

    addedGraphNode.emplace_back(Node(fromNode));

    //while not all nodes are in graph
    while(addedGraphNode.size() != NUMBER_OF_CELL) {
        //Choose a random node in graph
        Node randomNode = getRandomNode(addedGraphNode);
        //Connect to a random neighbor node that is not in graph
        std::vector<Node> neighbors = getUnvisitedNeighborNode(randomNode);
        Node randomNeighbor = getRandomNode(neighbors);
        //if there's no unvisited neighbor nodes -> skip this one;
        if (randomNeighbor.getData() == Node::UNDEFINED) {
            continue;
        } else {
//this shit is fucking suspicious
            graph.addEdge(randomNode.getData(), randomNeighbor.getData());
            //Add that neighbor to graph
            addedGraphNode.emplace_back(randomNeighbor);
        }

    }
    graph.printGraph();

}

/**
 * To choose a random node from a set.
 * No deletion or anything
 * @param nodeSet: this set might be addedGraphNode or getNeighborNode
 * @return a Node with data UNDEFINED when there's none to return, else return a random from nodeSet.
 */
// how about return a null node??
Node Maze::getRandomNode(std::vector<Node> nodeSet) {
    if (nodeSet.empty()) {
        return Node(Node::UNDEFINED);
    }
    int randomIndex = rand() % nodeSet.size();
    Node randomNode = nodeSet[randomIndex];

    return randomNode;
}

/**
 * Find all node that is a valid node and not added in graph next to the given node.
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
 * Check if a node n is already in graph.
 * A node in graph = a node in addedGraphNode = a node has neighbor
 * @param n
 * @return if it's already added in graph
 */
bool Maze::isInGraph(Node n) {
    return std::count(addedGraphNode.begin(), addedGraphNode.end(), n);
}

void Maze::printMaze() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            switch (cellStatus[i][j]) {
                case IS_WALL:
                    std::cout << "w";
                    break;
                case IS_PATH:
                    std::cout << "p";
            }

        }
        std::cout << std::endl;
    }

}





