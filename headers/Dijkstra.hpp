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

    Graph visitedPathGraph;

    Graph finalPathGraph;

    int totalPathCost;

    int currentNodeData;

    int fromNode = 0;

    int goalNode = Maze::NUMBER_OF_CELL - 1;

//    use vector because array size must be given in declaration
    std::vector<bool> open;
    std::vector<int> distance;
    std::vector<bool> closed;
    std::vector<int> previous;
    std::vector<int> finalPath;

    sf::Font font;
    std::vector<sf::Text> distanceText;


    void updateDistanceText(Node node, std::string newString);


    bool isOpenEmpty();

    bool isFound;

    int findMinDistanceNode();

    void traceBackFinalPath(int currentNode);

//    void drawFinalPath();

    bool isGraphSet;


public:
//    explicit is to prevent constructor from implicit convert param type
    explicit Dijkstra(const Graph &graph);

    Dijkstra();

    void setGraph(const Graph &graph);

    void findShortestPath(Graph graph);

//    [nodiscard] raises warning if the return value of the function is ignored
    [[nodiscard]] int getTotalPathCost() const;

    [[nodiscard]] const std::vector<int> &getFinalPath() const;

    void printGraph();

    void draw(sf::RenderTarget& target, sf::RenderStates state = sf::RenderStates::Default) const override;

};


#endif //DSA_DIJKSTRA_HPP
