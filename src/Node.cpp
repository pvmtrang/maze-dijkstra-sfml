//
// Created by tieu on 7/30/2021.
//

#include <iostream>
#include "Node.hpp"

const int Node::UNDEFINED;  //this is the definition of a (static) const. *mindblow*

Node::Node(int data) : data(data), xCoord(UNDEFINED), yCoord(UNDEFINED) {
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







