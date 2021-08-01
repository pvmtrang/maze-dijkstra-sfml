#include <iostream>
//#include <SFML/Graphics.hpp>
#include <Graph.hpp>
#include <Dijkstra.hpp>
#include "UnionFind.hpp"
#include "Node.hpp"
#include "Maze.hpp"
#include <string.h>
#include <algorithm>

int main() {
//    sf::Window window(sf::VideoMode(800, 600), "bla");

    /*static int WIDTH = 10;
    static int HEIGHT = 5;

    Graph g(7);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 5);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 6);
    g.addEdge(4, 6);
    g.addEdge(0, 2);

    g.printGraph();


    Dijkstra djk(g);

    if (djk.findShortestPath(0, 6)) {
        std::vector<int>output = djk.getFinalPath();
        std::cout << "final path: ";
        for(int i : output) {
            std::cout << i << " ";
        }
        std::cout << std::endl << "path cost: " << djk.getTotalPathCost();
    } else {
        std::cout << "no path found";
    }*/

    /*UnionFind u(10);
    u.connect(9, 7);
    u.connect(7, 3);
    u.connect(8, 0);
    u.connect(7, 0);
    u.connect(2, 5);
    u.connect(1, 5);
    u.connect(5, 6);
    u.connect(4,5);

//    u.connect(9, 1);
//    std::cout << u.isConnected(9, 1);
    u.printComponent();*/

    Maze maze;
    maze.generateMaze();
    std::cout << "weighted graph\n";
    maze.generateWeightedGraph();

    Dijkstra djk(maze.getWeightedGraph());
    djk.findShortestPath(0, 29);

//    std::cout << (-5) % 5;
    /*std::vector<int> tmp;
    for (int i = 0; i < 6; i++) {
        tmp.emplace_back(i);
    }

    std::swap(tmp[2], tmp[tmp.size() - 1]);

    tmp.pop_back();

    for (int i = 0; i < tmp.size(); i++) {
        std::cout << tmp[i] << " ";
    }*/

    /*std::vector<Node> tmp {Node(1), Node(2), Node(3), Node(2), Node(5), Node(4), Node(2)};
    int randomIndex = rand() % tmp.size();
    Node randomNode = tmp[randomIndex];
    std::cout << randomNode.getData();*/
    return 0;
}