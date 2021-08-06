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
    //manually update this whenever read maze from file
    static const int HORIZONTAL = 10;
    static const int VERTICAL = 10;
    static const int NUMBER_OF_CELL = HORIZONTAL * VERTICAL;

    Maze();

    void readMazeFromFile(std::string filePath);

    void generateMaze( sf::RenderTarget& target, int fromNode = 0);

    Graph getMazeGraph();

    void generateWeightedGraph();

    Graph getWeightedGraph();

    void draw(sf::RenderTarget& target, sf::RenderStates state = sf::RenderStates::Default) const override;

    bool isDone;


private:
    Graph mazeGraph;

    Graph weightedGraph;

    //cant make this local variable because not only generateMaze
    //it's also related to getUnvisitedNeighbor, and isInGraph
    std::vector<Node> addedToGraphNode;

    Node getRandomNode(std::vector<Node> nodeSet);

    bool isInGraph(Node n);

    std::vector<Node> getUnvisitedNeighborNode(Node n);

    bool isQualifiedForWeightedGraph(Node node);

    Node findNextQualifiedNode(Node node);

    //cant think of a better name =_=
    std::vector<Node> qualifiedNode;

    void findAllQualifiedNode();

    bool isWeightedGraphGenerated();

//    void createMultiplePath();




};


#endif //MAZE_SFML_MAZE_HPP
