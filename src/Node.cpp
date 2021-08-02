//
// Created by tieu on 7/30/2021.
//

#include <iostream>
#include "Node.hpp"
#include "Maze.hpp"
#include "Painter.hpp"
#include <SFML/Graphics.hpp>

const int Node::UNDEFINED;  //this is the definition of a (static) const. *mindblow*

Node::Node(int data) : data(data) {
    xCoord = data % Maze::WIDTH;
    yCoord = (data - xCoord) / Maze::WIDTH;

//    hmmm i'm using int for float vector hmmmm
    square.setFillColor(sf::Color::White);
    square.setSize(sf::Vector2f(NODE_SIZE, NODE_SIZE));
    square.setPosition(sf::Vector2f(getXCoord() * NODE_SIZE,
                                    getYCoord() * NODE_SIZE));
    square.setOutlineThickness(NODE_BORDER_SIZE);
    square.setOutlineColor(sf::Color::Red);
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







