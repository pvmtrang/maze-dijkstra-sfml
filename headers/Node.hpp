//
// Created by tieu on 7/30/2021.
//

#ifndef MAZE_SFML_NODE_HPP
#define MAZE_SFML_NODE_HPP


#include <SFML/Graphics.hpp>

class Node : public sf::Drawable {
private:
    int data;
//    according to sfml coordinate, xy on top left, x_ y|
    int xCoord;
    int yCoord;

    sf::RectangleShape square;

public:
    static const int UNDEFINED = -1;    ; //This is just the declaration, the def is in cpp
    static const int NODE_SIZE = 50;
    static const int NODE_BORDER_SIZE = -10;

    Node(int data);

    int getData() const;

    int getXCoord() const;

    int getYCoord() const;

//    is this equivalent to equals in java ?? :D wtf
    bool operator==(const Node &rhs) const;

    bool operator!=(const Node &rhs) const;

    sf::RectangleShape dgetShape();

    void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

};


#endif //MAZE_SFML_NODE_HPP
