#ifndef UNTITLED2_NODE_H
#define UNTITLED2_NODE_H

#include <stdbool.h>

typedef struct Node Node;
typedef struct Node {
    int posX;
    int posY;
    Node* prevNode;
    int T_intersection;
    bool visited;
   // Node* currentNode;
}Node;


#endif //UNTITLED2_NODE_H
#pragma once
