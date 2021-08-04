//
// Created by tieu on 7/30/2021.
//

#include <iostream>
#include "Node.hpp"
#include "Maze.hpp"

const int Node::UNDEFINED;  //this is the definition of a (static) const. *mindblow*


Node::Node(int data, sf::Color color) : data(data), color(color) {
    xCoord = data % Maze::WIDTH;
    yCoord = (data - xCoord) / Maze::WIDTH;
/*
    font.loadFromFile("assets/Abel-Regular.ttf");

    text.setFont(font);
    text.setString("haha");
    text.setCharacterSize(SIZE_NODE / 2);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(getXCoord() * SIZE_CELL + SIZE_BORDER + SIZE_NODE / 2,
                     getYCoord() * SIZE_CELL + SIZE_BORDER + SIZE_NODE / 2);*/


//    hmmm i'm using int for float vector hmmmm
    square.setFillColor(color);
    square.setSize(sf::Vector2f(SIZE_NODE, SIZE_NODE));
    square.setPosition(sf::Vector2f(getXCoord() * SIZE_CELL + SIZE_BORDER,
                                    getYCoord() * SIZE_CELL + SIZE_BORDER));
    //1 is for the square outline
    square.setOutlineThickness(1);
    square.setOutlineColor(sf::Color::Magenta);
}

/*sf::Font Node::loadFont() {
    sf::Font font;
    font.loadFromFile("assets/Abel-Regular.ttf");
    return font;
}*/

int Node::getData() {
    return data;
}

/*void Node::setText(std::string newText) {
    text.setString(newText);
}*/


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
//    target.draw(text);

}

sf::RectangleShape Node::getShape() {
    return sf::RectangleShape();
}














