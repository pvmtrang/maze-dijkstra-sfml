#include <iostream>
#include <SFML/Graphics.hpp>
#include <Graph.hpp>
#include <Dijkstra.hpp>
#include "UnionFind.hpp"
#include "Node.hpp"
#include "Maze.hpp"
#include <string.h>
#include <algorithm>

void takeInput(sf::RenderWindow &window) {
    sf::Event event{};

    while (window.pollEvent(event)) {
        // Window closed
        switch(event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window.close();
                }
            default:
                break;
        }
    }
}

int main() {
    static const int SCALED_WIDTH = Maze::WIDTH * Node::SIZE_NODE;
    static const int SCALED_HEIGHT = Maze::HEIGHT * Node::SIZE_NODE;

    std::vector<sf::RectangleShape> vec;
    int tmp = 0;

    sf::RenderWindow window(sf::VideoMode(SCALED_WIDTH, SCALED_HEIGHT), "Mazzzze", sf::Style::Default);
    window.setFramerateLimit(60);

    Graph g(200);

    while (window.isOpen()) {
        if (tmp < 150) {
            g.addEdge(tmp, tmp + 3);
            tmp += 1;
        }

        g.draw(window);


        window.display();
        window.clear(sf::Color::Black);
        takeInput(window);


    }
    window.setFramerateLimit(50);






//    Dijkstra djk(maze.getWeightedGraph());
//    djk.findShortestPath(0, 29);

    return 0;
}