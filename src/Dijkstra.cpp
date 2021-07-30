//
// Created by tieu on 7/28/2021.
//

#include <iostream>
#include <algorithm>
#include "Dijkstra.hpp"
#include "Graph.hpp"

const int Dijkstra::INFINITY;

//checked
Dijkstra::Dijkstra(const Graph &graph) : graph(graph) {
//    this->graph = graph;
    totalPathCost = 0;
    for (int i = 0; i < graph.getNumberOfNode(); i++) {
        open.push_back(true);
        closed.push_back(false);
        previous.push_back(Graph::UNDEFINED);
        distance.push_back(INFINITY);

    }
}

/**
 *To return if there is a path from fromNode to toNode.
 * Pretend that there's no number been skipped -> no check if it's in the list
 * @param fromNode
 * @param toNode
 * @return true if there's a path
 */
bool Dijkstra::findShortestPath(int fromNode, int toNode) {
    distance[fromNode] = 0;

    while(isOpenEmpty()) {
        int currentNode = findMinDistance();
        if (currentNode != Graph::UNDEFINED) {
            if (currentNode == toNode) {
                traceBackPath(currentNode);
                return true;
            }

            //remove from open
            open[currentNode] = false;

            std::vector<int> neighbor = graph.getNeighborNodes(currentNode);

            for(int n : neighbor) {
                if (!closed[n]) {
                    int tmp = distance[currentNode] + graph.getWeight(currentNode, n);
                    if(tmp < distance[n]) {
                        distance[n] = tmp;
                        previous[n] = currentNode;
                    }
                }
            }

            closed[currentNode] = true;
        }
    }

    return false;
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

void Dijkstra::traceBackPath(int currentNode) {
    totalPathCost = distance[currentNode];
    while(previous[currentNode] != Graph::UNDEFINED) {
        finalPath.push_back(currentNode);
//        std::cout << "current: " << currentNode << " ";
        currentNode = previous[currentNode];
    }
    std::reverse(finalPath.begin(),finalPath.end());
}

/**
 * Find the node with minimum distance among the open nodes.
 * @return the name aka the index of the node
 */
int Dijkstra::findMinDistance() {
    int minDist = INFINITY;
    int minNode = Graph::UNDEFINED;
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



