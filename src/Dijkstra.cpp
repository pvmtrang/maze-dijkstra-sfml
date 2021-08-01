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
    totalPathCost = INFINITY;
    for (int i = 0; i < graph.getNumberOfNode(); i++) {
        open.emplace_back(true);
        closed.emplace_back(false);
        previous.emplace_back(Node::UNDEFINED);
        distance.emplace_back(INFINITY);
    }
}

/**
 *To return if there is a path from fromNode to toNode.
 * Pretend that there's no number been skipped -> no check if it's in the list
 * @param fromNode
 * @param toNode
 * @return true if there's a path
 */
void Dijkstra::findShortestPath(int fromNode, int toNode) {
    distance[fromNode] = 0;

    while(isOpenEmpty()) {
        int currentNode = findMinDistance();
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
                    }
                }
            }
        }
    }
    std::cout << std::endl << "No path found" << std::endl;
//    return;
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
    totalPathCost = distance[currentNode];
    while(previous[currentNode] != Node::UNDEFINED) {
        finalPath.emplace_back(currentNode);
//        std::cout << "current: " << currentNode << " ";
        currentNode = previous[currentNode];
    }
    //add the starting node also
    finalPath.emplace_back(currentNode);
    std::reverse(finalPath.begin(),finalPath.end());
}

/**
 * Find the node with minimum distance among the open nodes.
 * @return node with undefined data when cant find the min distance aka. there's no closed neighbors left
 * else just return the node with min distance
 */
int Dijkstra::findMinDistance() {
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



