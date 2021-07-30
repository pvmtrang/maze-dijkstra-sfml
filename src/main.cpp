#include <iostream>
//#include <SFML/Graphics.hpp>
#include <Graph.hpp>
#include <Dijkstra.hpp>
#include "Union.hpp"
#include "Node.hpp"

int main() {
//    sf::Window window(sf::VideoMode(800, 600), "bla");

    static int WIDTH = 10;
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


    /*Dijkstra djk(g);

    if (djk.findShortestPath(0, 6)) {
        std::vector<int>output = djk.getFinalPath();
        std::cout << "final path: ";
        for(int i : output) {
            std::cout << i << " ";
        }
    } else {
        std::cout << "no path found";
    }*/

    /*Union u(10);
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



    return 0;
}