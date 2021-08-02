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
    static const int SCALED_WIDTH = Maze::WIDTH * Node::SIZE_CELL;
    static const int SCALED_HEIGHT = Maze::HEIGHT * Node::SIZE_CELL;

    sf::RenderWindow window(sf::VideoMode(SCALED_WIDTH, SCALED_HEIGHT), "Mazzzze", sf::Style::Default);
    window.setFramerateLimit(51);

    Maze maze;

//    Maze::countMazeGenerated = 0;
//    Graph g(30);


    while (window.isOpen()) {
        maze.generateMaze(window);

        maze.draw(window);

        window.display();
        window.clear(sf::Color::Black);
        takeInput(window);


    }

    std::cout << "finished";

//    Dijkstra djk(maze.getWeightedGraph());
//    djk.findShortestPath(0, 29);

    return 0;
}