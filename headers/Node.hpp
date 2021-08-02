//
// Created by tieu on 7/30/2021.
//

#ifndef MAZE_SFML_NODE_HPP
#define MAZE_SFML_NODE_HPP


#include <SFML/Graphics.hpp>

class Node : public sf::Drawable {
private:
    int data;
    //by sfml coordinate, xy on top left, x_ y|
    int xCoord;
    int yCoord;

    sf::RectangleShape square;

    sf::Color color;

public:
    static const int UNDEFINED = -1;    ; //This is just the declaration, the def is in cpp
    static const int SIZE_CELL = 40;
    static const int SIZE_BORDER = 10;
    static const int SIZE_NODE = SIZE_CELL - 2 * SIZE_BORDER;

    sf::Color COLOR_NODE {sf::Color::White};
//    const sf::Color COLOR_BORDER {sf::Color::Red};


    Node(int data = UNDEFINED, sf::Color color = sf::Color::White);

//    Node(Node &other);

    int getData();

    void setData(int data);

    int getXCoord() const;

    int getYCoord() const;

//    is this equivalent to equals in java ?? :D wtf
    bool operator==(const Node &rhs) const;

    bool operator!=(const Node &rhs) const;

    sf::RectangleShape getShape();

    void draw(sf::RenderTarget& target, sf::RenderStates state = sf::RenderStates::Default) const override;

};


#endif //MAZE_SFML_NODE_HPP
