//
// Created by tieu on 7/28/2021.
//

#include <iostream>
#include <algorithm>
#include "Dijkstra.hpp"
#include "Graph.hpp"

const int Dijkstra::INFINITY;

Dijkstra::Dijkstra() {
    totalPathCost = INFINITY;
    isGraphSet = false;
    isFound = false;

    font.loadFromFile("assets/Abel-Regular.ttf");

}

//checked
Dijkstra::Dijkstra(const Graph &graph) {
    totalPathCost = INFINITY;
    isFound = false;

    font.loadFromFile("assets/Abel-Regular.ttf");

    setGraph(graph);
}

void Dijkstra::setGraph(const Graph &graph) {
    Dijkstra::graph = graph;

    isGraphSet = true;

    currentNodeData = Node::UNDEFINED;

    std::cout << "graph is set" << std::endl;

    for (int i = 0; i < graph.getNumberOfNode(); i++) {
        open.emplace_back(true);
        closed.emplace_back(false);
        previous.emplace_back(Node::UNDEFINED);
        distance.emplace_back(INFINITY);

        distanceText.emplace_back(sf::Text("", font));
    }

    visitedPathGraph = Graph(graph.getNumberOfNode(), sf::Color::Green);
    finalPathGraph = Graph(graph.getNumberOfNode(), sf::Color::Red);
}

/**
 * Find the shortest path (if there's one) in graph between 2 nodes
 * @param graph: demonstrate better if it's weighted graph. Works like BFS with unweighted maze graph.
 * @param fromNode: node 0 default
 * @param goalNode: the last node in map defaul
 */
void Dijkstra::findShortestPath(Graph graph) {
    if (!isGraphSet) {
        setGraph(graph);
        distance[fromNode] = 0;

        //for rendering
        previous[fromNode] = fromNode;
        updateDistanceText(Node(fromNode), std::to_string(0));
    }
    if (!isFound) {
        //if - while
        if(isOpenEmpty()) {
            currentNodeData = findMinDistanceNode();
            Node currentNode(currentNodeData);

            std::cout << "NODE " << currentNodeData << " DISTANCE TO 0: " << distance[currentNodeData] << std::endl;

            //for rendering
            visitedPathGraph.addEdge(currentNode, Node(previous[currentNodeData]));

            //when there's still open neighbor
            if (currentNodeData != Node::UNDEFINED) {
                if (currentNodeData == goalNode) {
                    traceBackFinalPath(currentNodeData);
                    std::cout << std::endl << "final shortest path is: ";
                    for (int i : finalPath) {
                        std::cout << i << " ";
                    }
                    return;
                }

                //move node from open to closed
                open[currentNodeData] = false;
                closed[currentNodeData] = true;

                std::vector<Node> neighbor = graph.getNeighborNodes(currentNode);

                for(Node n : neighbor) {
                    if (!closed[n.getData()]) {
                        int tmp = distance[currentNodeData] + graph.getDistance(currentNode, n);
                        if(tmp < distance[n.getData()]) {
                            distance[n.getData()] = tmp;
                            previous[n.getData()] = currentNodeData;

                            updateDistanceText(n, std::to_string(tmp));
                        }
                    }
                }
            }
        }
    }
}


void Dijkstra::updateDistanceText(Node node, std::string newString) {
//    Node n(node);

    sf::Text text(newString, font);
    text.setCharacterSize(Node::SIZE_NODE * 0.75);
    text.setFillColor(sf::Color::Black);
    text.setPosition(node.getXCoord() * Node::SIZE_CELL + Node::SIZE_BORDER,
                     node.getYCoord() * Node::SIZE_CELL + Node::SIZE_BORDER);

    distanceText[node.getData()] = text;
}


/**
 * Check if there's still an open node left
 * @return true if there's still one node with open == true
 */
bool Dijkstra::isOpenEmpty() {
    for (int i = 0; i < open.size(); i++) {
        if (open[i]) {
            return true;
        }
    }
    return false;
}

void Dijkstra::traceBackFinalPath(int currentNode) {
    std::cout << "Is tracing back final path" << std::endl;
    totalPathCost = distance[currentNode];
    while(previous[currentNode] != currentNode) {
        finalPath.emplace_back(currentNode);
//        std::cout << "current: " << currentNodeList << " ";
        int prev = previous[currentNode];

        finalPathGraph.addEdge(Node(prev), Node(currentNode));

        currentNode = prev;


    }
    //add the starting node also
    finalPath.emplace_back(currentNode);


    isFound = true;

//    std::reverse(finalPath.begin(),finalPath.end());

}


/**
 * Find the node with minimum distance among the open nodes.
 * @return node with undefined data when cant find the min distance aka. there's no closed neighbors left
 * else just return the node with min distance
 */
int Dijkstra::findMinDistanceNode() {
    int minDist = INFINITY;
    int minNode = Node::UNDEFINED;
    for (int i = 0; i < open.size(); i++) {
        if (open[i]) {
            if (distance[i] < minDist) {
                minDist = distance[i];
                minNode = i;
            }
        }
    }
    return minNode;
}

void Dijkstra::printGraph() {
    graph.printGraph();
}

int Dijkstra::getTotalPathCost() const {
    return totalPathCost;
}

const std::vector<int> &Dijkstra::getFinalPath() const {
    return finalPath;
}

void Dijkstra::draw(sf::RenderTarget &target, sf::RenderStates state) const {
//    std::cout << "drawing djk graph" << std::endl;

    visitedPathGraph.draw(target, state);

    Node(currentNodeData, sf::Color::Red).draw(target, state);

    finalPathGraph.draw(target, state);

    for (int i = 0; i < distanceText.size(); i++) {
        target.draw(distanceText[i]);
    }

}






