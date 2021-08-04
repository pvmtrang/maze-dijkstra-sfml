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

    static const int SPEED_HIGH = 60;
    static const int SPEED_LOW = 10;

    sf::RenderWindow window(sf::VideoMode(SCALED_WIDTH, SCALED_HEIGHT), "Mazzzze", sf::Style::Default);
    window.setFramerateLimit(SPEED_HIGH);

    Maze maze;
    Dijkstra djk;

    sf::Font font;
    font.loadFromFile("assets/Abel-Regular.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);


    while (window.isOpen()) {
        maze.generateMaze(window);

        maze.draw(window);

        if (maze.isDone) {
            window.setFramerateLimit(SPEED_LOW);
            djk.findShortestPath(maze.getWeightedGraph());
            window.draw(djk);
        }

//        window.draw(text);
        window.display();
        window.clear(sf::Color::Black);
        takeInput(window);


    }

    std::cout << "finished";

//    maze.generateWeightedGraph();

    /*Dijkstra djk(maze.getWeightedGraph());
    djk.findShortestPath(0, 29);*/

    return 0;
}