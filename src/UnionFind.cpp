//
// Created by tieu on 7/29/2021.
//

#include <iostream>
#include "UnionFind.hpp"

UnionFind::UnionFind(int numberOfNode) : numberOfNode(numberOfNode) {
    //each node is on its own component
    for (int i = 0; i < numberOfNode; i++) {
        id.push_back(i);
    }
}

/**
 * To join two unions by point this root to another root.
 * More specific, make node1 point to node2
 * By path compression, make node1 and node2 directly point to the roots
 * @param node1
 * @param node2
 */
void UnionFind::connect(int node1, int node2) {
    int root1 = findRoot(node1);
    id[node1] = root1;
    int root2 = findRoot(node2);
    id[node2] = root2;
    id[root1] = root2;
}

/**
 * To find the root of a node using Path Compression.
 * @param node
 * @return the root
 */
int UnionFind::findRoot(int node) {
    while (id[node] != node) {
        //point the current node to its grandfather
        id[node] = id[id[node]];
        node = id[node];
    }
    return node;
}

//checked
bool UnionFind::isConnected(int node1, int node2) {
    return findRoot(node1) == findRoot(node2);
}

//checked
void UnionFind::printComponent() {
    int currentNode = 0;
    std::vector<std::vector<int>> output;
    while (currentNode < numberOfNode) {
        int isIncluded = false;
        for (int i = 0; i < output.size(); i++) {
            //if the currentNode belong to any component -> add
            if (isConnected(currentNode, output[i][0])) {
                output[i].push_back(currentNode);
                isIncluded = true;
                break;
            }
        }
        //else create a new component and add
        if (!isIncluded) {
            output.push_back(std::vector<int>());
            output[output.size() - 1].push_back(currentNode);
        }
        currentNode++;
    }

    for (int i = 0; i < output.size(); i++) {
        std::cout << i + 1 << ": ";
        for (int j = 0; j <output[i].size(); j++) {
            std::cout << "-" << output[i][j];
        }
        std::cout << std::endl;
    }

}
