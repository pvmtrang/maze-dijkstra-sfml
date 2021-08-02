//
// Created by tieu on 7/28/2021.
//

#ifndef DSA_DIJKSTRA_HPP
#define DSA_DIJKSTRA_HPP


#include "Graph.hpp"
#include "Maze.hpp"

/**
 * vector open, distance, closed, previous store status of node
 * node is equal to index
 */
class Dijkstra : public sf::Drawable {
private:
    static const int INFINITY = INT_MAX;

    Graph graph;

    Graph finalPathGraph;

    Graph tmp;

    int totalPathCost;
//    use vector because array size must be given in declaration
    std::vector<bool> open;
    std::vector<int> distance;
    std::vector<bool> closed;
    std::vector<int> previous;
    std::vector<int> finalPath;

    bool isOpenEmpty();

    bool isFound;

    int findMinDistanceNode();

    void traceBackFinalPath(int currentNode);

    void drawFinalPath();

    void draw(sf::RenderTarget& target, sf::RenderStates state = sf::RenderStates::Default) const override;

    bool isGraphSet;

    std::vector<int> currentNodeList;

public:
//    explicit is for prevent constructor from implicit convert param type
    explicit Dijkstra(const Graph &graph);

    Dijkstra();

    void setGraph(const Graph &graph);

    void findShortestPath(Graph graph, int fromNode = 0, int ToNode = Maze::NUMBER_OF_CELL - 1);

//    [nodiscard] raises warning if the return value of the function is ignored
    [[nodiscard]] int getTotalPathCost() const;

    [[nodiscard]] const std::vector<int> &getFinalPath() const;

    void printGraph();


};


#endif //DSA_DIJKSTRA_HPP
