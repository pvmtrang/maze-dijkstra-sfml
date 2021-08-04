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

//    finalPathGraph(0);
}

//checked
Dijkstra::Dijkstra(const Graph &graph) {
    setGraph(graph);
    /*totalPathCost = INFINITY;
    for (int i = 0; i < graph.getNumberOfNode(); i++) {
        open.emplace_back(true);
        closed.emplace_back(false);
        previous.emplace_back(Node::UNDEFINED);
        distance.emplace_back(INFINITY);
    }*/
}

void Dijkstra::setGraph(const Graph &graph) {
//    Dijkstra(graph);
    Dijkstra::graph = graph;

    isGraphSet = true;

    std::cout << "graph is set" << std::endl;

    totalPathCost = INFINITY;

    currentNode = Node::UNDEFINED;

    for (int i = 0; i < graph.getNumberOfNode(); i++) {
        open.emplace_back(true);
        closed.emplace_back(false);
        previous.emplace_back(Node::UNDEFINED);
        distance.emplace_back(INFINITY);
    }

    finalPathGraph = Graph(graph.getNumberOfNode(), sf::Color::Green);
    tmp = Graph(graph.getNumberOfNode(), sf::Color::Red);
}

/**
 * Find the shortest path (if there's one) in graph between 2 nodes
 * @param graph: demonstrate better if it's weighted graph. Works like BFS with unweighted maze graph.
 * @param fromNode: node 0 default
 * @param toNode: the last node in map defaul
 */
void Dijkstra::findShortestPath(Graph graph, int fromNode, int toNode) {
    if (!isGraphSet) {
        setGraph(graph);
        distance[fromNode] = 0;

        //for rendering
        previous[fromNode] = fromNode;
    }
    if (!isFound) {
        //if - while
        if(isOpenEmpty()) {

//            std::cout << "check djk open empty" << std::endl;
//            int currentNode = findMinDistanceNode();
            currentNode = findMinDistanceNode();
            std::cout << "NODE " << currentNode << " DISTANCE TO 0: " << distance[currentNode] << std::endl;
//            std::cout << "from previous node is " << previous[currentNode] << std::endl;


            //for rendering
//            currentNodeList.clear();
//            currentNodeList.emplace_back(currentNode);
//            currentNodeToRender = currentNode;

            //for rendering
            finalPathGraph.addEdge(currentNode, previous[currentNode]);

//            std::cout << "CURRENT NODEEEE " << currentNode << std::endl;
            //when there's still open neighbor
            if (currentNode != Node::UNDEFINED) {
                if (currentNode == toNode) {
                    traceBackFinalPath(currentNode);
                    std::cout << std::endl << "final shortest path is: ";
                    for (int i : finalPath) {
                        std::cout << i << " ";
                    }
                    return;
                }

                //remove from open
                open[currentNode] = false;
                closed[currentNode] = true;

                std::vector<int> neighbor = graph.getNeighborNodes(currentNode);

                for(int n : neighbor) {
                    if (!closed[n]) {
                        int tmp = distance[currentNode] + graph.getDistance(currentNode, n);
                        if(tmp < distance[n]) {
                            distance[n] = tmp;
                            previous[n] = currentNode;



//                            currentNodeList.emplace_back(n);
                        }
                    }
                }
            }
        }
    }
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

        tmp.addEdge(prev, currentNode);

        currentNode = prev;


    }
    //add the starting node also
    finalPath.emplace_back(currentNode);

//    drawFinalPath();

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

    finalPathGraph.draw(target, state);

    Node(currentNode, sf::Color::Red).draw(target, state);

    /*for (int i = 0; i < currentNodeList.size(); i++) {
//        std::cout << "IS THIS FUCKING CURRENT NODE " << i << "BEING DRAWN?" << std::endl;
        Node(currentNodeList[i], sf::Color::Red).draw(target, state);
    }*/

    tmp.draw(target, state);

}



