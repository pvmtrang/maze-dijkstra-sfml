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
    //??? /2
    square.setSize(sf::Vector2f(SIZE_NODE, SIZE_NODE));
    square.setPosition(sf::Vector2f(getXCoord() * SIZE_CELL + SIZE_BORDER,
                                    getYCoord() * SIZE_CELL + SIZE_BORDER));
//    square.setOutlineThickness(1);
//    square.setOutlineColor(sf::Color::Red);
}

//Node::Node(Node &other) {
//    Node(other.getData());
//}

int Node::getData() {
    return data;
}

void Node::setData(int data) {
    Node::data = data;
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











