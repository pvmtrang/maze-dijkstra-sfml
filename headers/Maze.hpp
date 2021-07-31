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

    void generateMaze(int fromNode);

private:
    static const int IS_PATH = 1;
    static const int IS_WALL = 0;
    static const char PATH = ' ';
    static const char WALL = '#';

    Graph graph;

    bool cellStatus[HEIGHT][WIDTH];
    std::vector<Node> addedGraphNode;

    Node getRandomNode(std::vector<Node> nodeSet);

    bool isInGraph(Node n);

    std::vector<Node> getUnvisitedNeighborNode(Node n);
    void printMaze();

};


#endif //MAZE_SFML_MAZE_HPP
