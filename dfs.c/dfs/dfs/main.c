#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "node.h"
#include "dfs.h"
#include "queue.h"

/*
int map[Map_size_test][Map_size_test] = {
    // 0 1 2 3 4 5 6 7 8 9
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // 0
    {0, 0, 1, 0, 0, 0, 1, 0, 0, 1}, // 1
    {0, 0, 1, 1, 1, 1, 1, 0, 0, 1}, // 2
    {0, 0, 1, 0, 0, 0, 0, 1, 1, 1}, // 3
    {0, 0, 1, 1, 1, 0, 0, 1, 0, 0}, // 4
    {0, 0, 0, 0, 1, 0, 0, 1, 1, 1}, // 5
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 1}, // 6
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 1}, // 7
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 1}, // 8
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 1}  // 9
    // 0 1 2 3 4 5 6 7 8 9
};*/

int map[map_size_rows][map_size_cols] = {
   //0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},//0
    {1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1},
    {1,1,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1},
    {1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1},
    {1,0,1,0,1,0,1,1,1,0,1,0,1,1,1,0,1,0,1},
    {1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,1},
    {1,0,1,1,1,1,1,1,1,0,0,0,1,1,1,0,1,0,1},
    {1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,1},
    {1,1,1,0,0,0,1,1,1,1,1,0,1,0,1,0,1,0,1},
    {1,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1},
    {1,0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,0,1},
    {1,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,1},
    {1,1,1,1,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1},
    {0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };

int map2[map_size_rows][map_size_cols] = {
    //0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8 
     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //0
     {0,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,0}, //1
     {0,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,1,0}, //2
     {0,1,1,1,0,1,0,1,1,1,0,1,1,1,1,1,0,1,0}, //3
     {0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0}, //4
     {0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0}, //5
     {0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0}, //6 
     {0,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,0}, //7
     {0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0}, //8
     {0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0}, //9
     {0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,1,0,1,0}, //10
     {0,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0}, //11
     {0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0}, //12
     {0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,0}, //13 
     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}  //14
};

/*
int map_path[map_size_rows][map_size_cols] = {
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
};*/

int start[2] = { 1,1 };
//int dest[2] = { 5,17 };
//int dest[2] = { 8,3 };
int dest[2] = { 10,10 };

int pathArray[300][3];

int i, j;

int pathNode[300][2];




int getShortestPath(int mapArray[map_size_rows][map_size_cols], int startPos[2], int destPos[2], int shortestPath[][3], int level) {
    // PARSE DATA
    printf("PARSING DATA\n");
    Node* nodeMapArray[map_size_rows][map_size_cols];
    parseMapData(nodeMapArray, mapArray);

    Node* currentNode = bfs(nodeMapArray, startPos, destPos);
    //Node* currentNode;

    int listCount = 0;
    int k = 0;
    //printf("\n(%d,%d) <- ", currentNode->posX, currentNode->posY);

    if (level == 1) {
        Node* nodePath[300];   //nodePath is used to keep track of which node dfs traverses
        dfs(nodeMapArray, startPos, &listCount, nodePath);
        int i = 0;
        for (i = 0; i <= listCount - 1; i++) {
            shortestPath[i][0] = nodePath[i]->posY;
            shortestPath[i][1] = nodePath[i]->posX;
            shortestPath[i][2] = nodePath[i]->T_intersection;
        }
    }else if(level==2){
        while (currentNode->prevNode != NULL) {
            shortestPath[listCount][0] = currentNode->posY;
            shortestPath[listCount][1] = currentNode->posX;
            shortestPath[listCount][2] = currentNode->T_intersection;
            currentNode = currentNode->prevNode;
            printf("(%d,%d,%d) <- ", shortestPath[listCount][0], shortestPath[listCount][1], shortestPath[listCount][2]);
            pathNode[k][0] = shortestPath[listCount][0];
            pathNode[k][1] = shortestPath[listCount][1];
            listCount++;
            k++;
            
        }
    }
    pathNode[k][0] = start[0];
    pathNode[k][1] = start[1];
    putchar('\n');
    putchar('\n');

    printf("Path From Start to Destination is");
    putchar('\n');

    for (i = listCount; i >= 0; i--) {
        printf("(%d, %d) ->", pathNode[i][0], pathNode[i][1]);
    }

    return listCount;
}


void findAdjacentNodes(Node* currentNode, Node* nodeArray[map_size_rows][map_size_cols], Node* adjacentNodes[]) {
    // FIRST RESET ADJACENT ARRAY
    for (int i = 0; i < 4; i++) {
        adjacentNodes[i] = NULL;
    }

    // CHECKING LEFT
    if ((currentNode->posX > 0) && (nodeArray[currentNode->posY][currentNode->posX - 1]->posY != INVALID)) {
        adjacentNodes[0] = nodeArray[currentNode->posY][currentNode->posX - 1];
    }
    else {
        adjacentNodes[0] = NULL;
    }

    // CHECKING RIGHT
    if ((currentNode->posX < map_size_cols - 1) && (nodeArray[currentNode->posY][currentNode->posX + 1]->posY != INVALID)) {
        adjacentNodes[1] = nodeArray[currentNode->posY][currentNode->posX + 1];
    }
    else {
        adjacentNodes[1] = NULL;
    }

    // CHECKING ABOVE
    if ((currentNode->posY > 0) && (nodeArray[currentNode->posY - 1][currentNode->posX]->posY != INVALID)) {
        adjacentNodes[2] = nodeArray[currentNode->posY - 1][currentNode->posX];
    }
    else {
        adjacentNodes[2] = NULL;
    }

    // CHECKING BELOW
    if ((currentNode->posY < map_size_rows - 1) && (nodeArray[currentNode->posY + 1][currentNode->posX]->posY != INVALID)) {
        adjacentNodes[3] = nodeArray[currentNode->posY + 1][currentNode->posX];
    }
    else {
        adjacentNodes[3] = NULL;
    }

}

void parseMapData(Node* nodeMapArray[map_size_rows][map_size_cols], int mapArray[map_size_rows][map_size_cols]) {
    printf("IN FOR LOOP\n");
    for (int i = 0; i < map_size_rows; i++) {
        for (int j = 0; j < map_size_cols; j++) {
            nodeMapArray[i][j] = (Node *)malloc(sizeof(Node));   // allocate memory for node
            if (mapArray[i][j] == 0) {
                nodeMapArray[i][j]->posY = i;
                nodeMapArray[i][j]->posX = j;
                nodeMapArray[i][j]->prevNode = NULL;
                nodeMapArray[i][j]->visited = false;
            }
            else {
                nodeMapArray[i][j]->posY = INVALID;
            }
        }
    }


}

Node* bfs(Node* nodeMapArray[][map_size_cols], int startPos[2], int destPos[2]) {
    // CREATE QUEUE
    printf("CREATING QUEUE\n");
    int head, tail;
    Node* queue[450];
    initQueue(&head, &tail);

    // CALCULATE PATH
    printf("CALCULATING PATH\n");
    Node* currentNode = NULL;
    Node* startNode = nodeMapArray[startPos[0]][startPos[1]];
    Node* destNode = nodeMapArray[destPos[0]][destPos[1]];
    startNode->visited = true;   // label starting node as discovered
    enqueue(queue, &tail, startNode);
    while (head != tail) {   // the queue is empty when the head and tail pointers point to the same position
        currentNode = dequeue(queue, &head);
        printf("CURRENT NODE X: %d Y: %d\n", currentNode->posX, currentNode->posY);

        Node* adjacentNodes[4];
        int adjacentCount = 0;

        findAdjacentNodes(currentNode, nodeMapArray, adjacentNodes);

        for (int i = 0; i < 4; i++) {   // for every adjacent node
            if (adjacentNodes[i] != NULL) {
                adjacentCount++;
                if (adjacentNodes[i]->visited == false) {   // if adjacent node exists and hasn't been visited
                    adjacentNodes[i]->visited = true;           // set visited
                    adjacentNodes[i]->prevNode = currentNode;   // set parent node
                    enqueue(queue, &tail, adjacentNodes[i]);     // enqueue adjacent node
                }
            }
        }

        if (adjacentCount > 2) {    // more than two neighbours for current node
            currentNode->T_intersection = T_INTERSECTION;
        }
        else {
            currentNode->T_intersection = NO_T_INTERSECTION;
        }
        if (currentNode->posY == destNode->posY && currentNode->posX == destNode->posX) {
            //usbPutString("PATH FOUND\r\n");
            printf("PATH FOUND\r\n");
            break;

        }
    }

    return currentNode;
}

void dfs_r(Node * nodeMapArray[][map_size_cols], Node * sourceNode, int* listCount, Node * nodePath[]) {
        Node* currentNode = sourceNode;
        Node* adjacentNodes[4];
        int adjacentCount = 0;

        currentNode->visited = 1;
        nodePath[*listCount] = currentNode;
        (*listCount)++;

        findAdjacentNodes(currentNode, nodeMapArray, adjacentNodes);
        int i = 0;
        for (i = 0; i < 4; i++) {   // for every adjacent node
            if (adjacentNodes[i] != NULL) {
                adjacentCount++;
                if (adjacentCount > 2) {    // more than two neighbours for current node
                    currentNode->T_intersection = true; //1 = true
                }

                if (adjacentNodes[i]->visited == false) {   // if adjacent node exists and hasn't been visited (0 = false)
                    dfs_r(nodeMapArray, adjacentNodes[i], listCount, nodePath);
                    nodePath[(*listCount)] = currentNode;
                    (*listCount)++;
                }
            }
        }
}

// depth first search using recursion, calls recursive function
void dfs(Node* nodeMapArray[][map_size_cols], int startPos[2], int* listCount, Node* nodePath[]) {
    Node* sourceNode = nodeMapArray[startPos[0]][startPos[1]];
    dfs_r(nodeMapArray, sourceNode, listCount, nodePath);
}


int main() {
    int pathArrayLength;
    pathArrayLength = getShortestPath(map, start, dest, pathArray, 2); //Calculate the path
    //pathArrayLength = getShortestPath(map, start, dest, pathArray);
    printf("DONE\n");
}