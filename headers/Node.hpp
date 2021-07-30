//
// Created by tieu on 7/30/2021.
//

#ifndef MAZE_SFML_NODE_HPP
#define MAZE_SFML_NODE_HPP


class Node {
private:
    const int data;
//    according to sfml coordinate, xy on top left, x_ y|
    int xCoord;
    int yCoord;
public:
    static const int UNDEFINED = -1;    ; //This is just the declaration, the def is in cpp

    Node(int data);

    int getData() const;

    int getXCoord() const;

    int getYCoord() const;

//    is this equivalent to equals in java ?? :D wtf
    bool operator==(const Node &rhs) const;

    bool operator!=(const Node &rhs) const;


};


#endif //MAZE_SFML_NODE_HPP
