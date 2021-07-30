//
// Created by tieu on 7/28/2021.
//

#ifndef DSA_DIJKSTRA_HPP
#define DSA_DIJKSTRA_HPP


#include "Graph.hpp"

class Dijkstra {
private:
    static const int INFINITY = INT_MAX;

    Graph graph;
    int totalPathCost;
//    use vector because array size must be given in declaration
    std::vector<bool> open;
    std::vector<int> distance;
    std::vector<bool> closed;
    std::vector<int> previous;
    std::vector<int> finalPath;

    bool isOpenEmpty();

    int findMinDistance();

    void traceBackPath(int currentNode);

public:
//    explicit is for prevent constructor from implicit convert param type
    explicit Dijkstra(const Graph &graph);

    bool findShortestPath(int fromNode, int ToNode);

//    [nodiscard] raises warning if the return value of the function is ignored
    [[nodiscard]] int getTotalPathCost() const;

    [[nodiscard]] const std::vector<int> &getFinalPath() const;

    void printGraph();


};


#endif //DSA_DIJKSTRA_HPP
