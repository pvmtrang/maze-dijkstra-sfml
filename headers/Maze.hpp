//
// Created by tieu on 7/31/2021.
//

#ifndef MAZE_SFML_MAZE_HPP
#define MAZE_SFML_MAZE_HPP

#include <vector>
#include <Node.hpp>
#include <Graph.hpp>
#include <SFML/Graphics.hpp>

class Maze : public sf::Drawable {
public:
    static const int WIDTH = 12;
    static const int HEIGHT = 8;
    static const int NUMBER_OF_CELL = WIDTH * HEIGHT;

    Maze();

    void generateMaze( sf::RenderTarget& target, int fromNode = 0);

    Graph getMazeGraph();

    void generateWeightedGraph();

    Graph getWeightedGraph();

    void draw(sf::RenderTarget& target, sf::RenderStates state = sf::RenderStates::Default) const override;

    bool isDone;

private:
//    const sf::Color COLOR_MAZE_GRAPH{ sf::Color::Cyan};
//    const sf::Color COLOR_WEIGHTED_GRAPH{sf::Color::Green};

    Graph mazeGraph;

    Graph weightedGraph;

    //cant make this local variable because not only generateMaze
    //it's also related to getUnvisitedNeighbor, and isInGraph
    std::vector<Node> addedToGraphNode;

    Node getRandomNode(std::vector<Node> nodeSet);

    bool isInGraph(Node n);

    std::vector<Node> getUnvisitedNeighborNode(Node n);

    bool isQualifiedForWeightedGraph(int node);

    int findNextQualifiedNode(int node);

    //cant think of a better name =_=
    std::vector<int> qualifiedNode;

    void findAllQualifiedNode();

    bool isWeightedGraphGenerated();




};


#endif //MAZE_SFML_MAZE_HPP
