//
// Created by tieu on 7/31/2021.
//

#ifndef MAZE_SFML_MAZE_HPP
#define MAZE_SFML_MAZE_HPP


#include <vector>
#include <Node.hpp>
#include <Graph.hpp>

class Maze {
public:
    static const int WIDTH = 6;
    static const int HEIGHT = 5;
    static const int NUMBER_OF_CELL = WIDTH * HEIGHT;

    Maze();

    void generateMaze(int fromNode = 0);

    Graph getMazeGraph();

    void generateWeightedGraph();

    Graph getWeightedGraph();

private:
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

    void printMaze();

};


#endif //MAZE_SFML_MAZE_HPP
