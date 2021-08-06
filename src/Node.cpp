//
// Created by tieu on 7/30/2021.
//

#include <iostream>
#include "Node.hpp"
#include "Maze.hpp"

const int Node::UNDEFINED;  //this is the definition of a (static) const. *mindblow*


Node::Node(int data, sf::Color color1) : data(data), color(color1) {
    xCoord = data % Maze::HORIZONTAL;
    yCoord = (data - xCoord) / Maze::HORIZONTAL;

//    hmmm i'm using int for float vector hmmmm
    square.setFillColor(color);
    square.setSize(sf::Vector2f(SIZE_NODE, SIZE_NODE));
    square.setPosition(sf::Vector2f(getXCoord() * SIZE_CELL + SIZE_BORDER,
                                    getYCoord() * SIZE_CELL + SIZE_BORDER));
    //1 is for the square outline
//    square.setOutlineThickness(1);
//    square.setOutlineColor(sf::Color::Magenta);
}

int Node::getData() {
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


void Node::draw(sf::RenderTarget &target, sf::RenderStates state) const {
    target.draw(square);
}

sf::RectangleShape Node::getShape() {
    return sf::RectangleShape();
}

void Node::setColor(const sf::Color &color) {
    Node::color = color;
}














