//
// Created by tieu on 7/29/2021.
//

#include "Union.hpp"

Union::Union(int numberOfNode) : numberOfNode(numberOfNode) {
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
void Union::connect(int node1, int node2) {
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
int Union::findRoot(int node) {
    while (id[node] != node) {
        //point the current node to its grandfather
        id[node] = id[id[node]];
        node = id[node];
    }
    return node;
}

bool Union::isConnected(int node1, int node2) {
    return findRoot(node1) == findRoot(node2);
}
