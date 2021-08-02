//
// Created by tieu on 7/30/2021.
//

#include <iostream>
#include "Node.hpp"
#include "Maze.hpp"
#include <SFML/Graphics.hpp>

const int Node::UNDEFINED;  //this is the definition of a (static) const. *mindblow*

Node::Node(int data) : data(data) {
    xCoord = data % Maze::WIDTH;
    yCoord = (data - xCoord) / Maze::WIDTH;

//    hmmm i'm using int for float vector hmmmm
    square.setFillColor(COLOR_NODE);
    square.setSize(sf::Vector2f(SIZE_NODE, SIZE_NODE));
    square.setPosition(sf::Vector2f(getXCoord() * SIZE_NODE,
                                    getYCoord() * SIZE_NODE));
    square.setOutlineThickness(SIZE_BORDER);
    square.setOutlineColor(COLOR_BORDER);
}

int Node::getData() const {
    return data;
}

int Node::getXCoord() const {
    return xCoord;
}

int Node::getYCoord() const {
    return yCoord;
}

bool Node::operator==(const Node &rhs) const {
    return data == rhs.data;
}

bool Node::operator!=(const Node &rhs) const {
    return !(rhs == *this);
}
//
//void Node::render(sf::RenderWindow &window, sf::Color color) {
////    square.setFillColor(color);
//    window.draw(getShape());
//}

sf::RectangleShape Node::getShape() {
    return square;
}

void Node::draw(sf::RenderTarget &target, sf::RenderStates state) const {
    target.draw(square);

}







