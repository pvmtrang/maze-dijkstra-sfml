//
// Created by tieu on 7/31/2021.
//

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "Maze.hpp"

Maze::Maze() : mazeGraph(NUMBER_OF_CELL), weightedGraph(NUMBER_OF_CELL) {
    srand((int) time(nullptr));
    isDone = false;
}

/**
 * Using prim to generate maze
 * @param fromNode
 */
 //how to improve this
 //because of recursion, method with fromNode = 0 is called repeatedly for every frame loop
 //the bigger it grows, the slower it gets
void Maze::generateMaze( sf::RenderTarget& target, int fromNode) {
    //while not all nodes are in mazeGraph
    if (addedToGraphNode.size() < NUMBER_OF_CELL) {
        std::cout << "is drawing maze from node " << fromNode << std::endl;

        if (!isInGraph(Node(fromNode))) {
            addedToGraphNode.emplace_back(Node(fromNode));
        }
        //Choose a random node in mazeGraph
        Node randomNode = getRandomNode(addedToGraphNode);
        //Connect to a random neighbor node that is not in mazeGraph
        std::vector<Node> neighbors = getUnvisitedNeighborNode(randomNode);
        Node randomNeighbor = getRandomNode(neighbors);
        //if there's no unvisited neighbor nodes -> skip this one;
        if (randomNeighbor.getData() != Node::UNDEFINED) {
            mazeGraph.addEdge(randomNode, randomNeighbor);

            draw(target);

            generateMaze(target, randomNeighbor.getData());
        }
    } else {
        if (!isWeightedGraphGenerated()) {
            generateWeightedGraph();
        }

    }
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
        Node up(upY * HORIZONTAL + upX);
        if (!isInGraph(up)) {
            output.emplace_back(up);
        }
    }
    if (downY < VERTICAL) {
        Node down(downY * HORIZONTAL + downX);
        if (!isInGraph(down)) {
            output.emplace_back(down);
        }
    }
    if (leftX >= 0) {
        Node left(leftY * HORIZONTAL + leftX);
        if (!isInGraph(left)) {
            output.emplace_back(left);
        }
    }
    if (rightX >= 0) {
        Node right(rightY * HORIZONTAL + rightX);
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

void Maze::findAllQualifiedNode() {
    for (Node n : addedToGraphNode) {
        if (isQualifiedForWeightedGraph(n)) {
            qualifiedNode.emplace_back(n);
        }
    }
    /*for (int i = 0; i < mazeGraph.getNumberOfNode(); i++) {
        if (isQualifiedForWeightedGraph(i)) {
            qualifiedNode.emplace_back(i);
        }
    }*/
}



//Chua nghi den viec them start va end node vao kieu gi
//Or de mac dinh start la 0 va end la 29: 2 node nay luon qualified
void Maze::generateWeightedGraph() {
//1. find all possible qualified node
//    std::vector<int> qualifiedNode;
    findAllQualifiedNode();
//2. generate the weighted graph
    for (Node iQualifiedNode : qualifiedNode) {
        //loop through it's neighbor
        for (Node iNeighbor : mazeGraph.getNeighborNodes(iQualifiedNode)) {
            //if that neighbor is qualified -> create an edge for weighted graph
            if (isQualifiedForWeightedGraph(iNeighbor)) {
                weightedGraph.addEdge(iQualifiedNode, iNeighbor);
            } else {
            // dig depth into neighbor's neighbor until reach the first qualified node
                Node nextQualified = findNextQualifiedNode(iNeighbor);
                weightedGraph.addEdge(iQualifiedNode, nextQualified);

            }
        }
    }

    std::cout << "Done generating weighted graph" << std::endl;



    isDone = true;

//    weightedGraph.printGraph();
}

//this is like depth first search without backtracking
//take the first neighbor in the neighbor set
//and keep digging into that first neighbor's first neighbor
//get neighbor node only return it's neighbor node, not include the node itself
Node Maze::findNextQualifiedNode(Node node) {
    Node firstNeighbor = mazeGraph.getNeighborNodes(node)[0];
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
bool Maze::isQualifiedForWeightedGraph(Node node) {
//    std::vector<int> neighbor = mazeGraph.getNeighborNodes(node);
    std::vector<Node> neighbor = mazeGraph.getNeighborNodes(node);
    switch (neighbor.size()) {
        case 0: {//might not happen. Forse
            return false;
        }
        case 1: {// 1 neighbor = a dead end
            return true;
        }
        case 2: {
            Node n1 = neighbor[0];
            Node n2 = neighbor[1];
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

void Maze::draw(sf::RenderTarget &target, sf::RenderStates state) const {
    for (int i = 0; i < addedToGraphNode.size(); i++) {
        target.draw(addedToGraphNode[i]);
    }
    mazeGraph.draw(target);

    for (int i = 0; i < qualifiedNode.size(); i++) {
        target.draw(qualifiedNode[i]);
    }

}

bool Maze::isWeightedGraphGenerated() {
//    std::cout << "Check if weihted graph is generated" << std::endl;
    for (int i = 0; i < weightedGraph.getNumberOfNode(); i++) {
//        std::vector<int> neighbor = weightedGraph.getNeighborNodes(i);
//because every list has a default element which is itself
        if (weightedGraph.getNeighborNodes(Node(i)).size() > 1) {
            return true;
        }
    }
    return false;
}

void Maze::readMazeFromFile(std::string filePath) {
    std::ifstream file(filePath);
    std::vector<std::string> map;
    std::string line;

    while (std::getline(file, line)) {
        std::cout << line << std::endl;
        map.emplace_back(line);
    }

    int height = map.size();
    int length = map[0].size();

    int vertical = (height + 1) / 2;
    int horizontal = (length + 1) / 2;

    for (int i = 0; i < height; i += 2) {
        for (int j = 0; j < length; j += 2) {
            switch (map[i][j]) {
                case '*': {
                    int nodeData = (i / 2) * horizontal + (j / 2);
                    Node thisNode(nodeData);
                    addedToGraphNode.emplace_back(thisNode);
                    //check right
                    if (j + 1 < length && map[i][j + 1] == '+') {
                        Node rightNode(nodeData + 1);
                        mazeGraph.addEdge(thisNode, rightNode);
                    }
                    //check down
                    if (i + 1 < height && map[i + 1][j] == '+') {
                        Node downNode(nodeData + horizontal);
                        mazeGraph.addEdge(thisNode, downNode);
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }
    generateWeightedGraph();
}
