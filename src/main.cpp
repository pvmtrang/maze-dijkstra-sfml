#include <iostream>
#include <SFML/Graphics.hpp>
#include <Graph.hpp>
#include <Dijkstra.hpp>
#include "UnionFind.hpp"
#include "Node.hpp"
#include "Maze.hpp"
#include "Painter.hpp"
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
    static const int SCALED_WIDTH = Maze::WIDTH * Node::NODE_SIZE;
    static const int SCALED_HEIGHT = Maze::HEIGHT * Node::NODE_SIZE;

    std::vector<Node> vec;
    int tmp = 0;

    sf::RenderWindow window(sf::VideoMode(SCALED_WIDTH, SCALED_HEIGHT), "Mazzzze", sf::Style::Default);
    window.setFramerateLimit(10);

    while (window.isOpen()) {
        if (tmp < 10) {
            vec.emplace_back(Node(tmp));
            tmp += 1;
        } else {
            tmp = 0;
            vec.clear();
        }
        for (int i = 0; i < vec.size(); i++) {
            window.draw(vec[i]);
        }
        window.display();
        window.clear(sf::Color::Black);
        takeInput(window);


    }
    window.setFramerateLimit(50);






//    Dijkstra djk(maze.getWeightedGraph());
//    djk.findShortestPath(0, 29);

    return 0;
}