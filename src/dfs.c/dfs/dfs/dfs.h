#ifndef MAIN_H
#define MAIN_H

#define map_size_cols 19
#define map_size_rows 15
#define INVALID 250

#define T_INTERSECTION 1
#define NO_T_INTERSECTION 0

int getShortestPath(int mapArray[map_size_rows][map_size_cols], int startPos[2], int destPos[2], int shortestPath[][3], int level, int pellets[5][2]);
//uint8 getShortestPath(uint8 mapArray[MAX_SIZE_Y][MAX_SIZE_X], uint8 sourcePos[2], uint8 destPos[2], uint8 shortestPath[][3], uint8 level);
void findAdjacentNodes(Node* currentNode, Node* nodeArray[map_size_rows][map_size_cols], Node* adjacentNodes[]);
void parseMapData(Node* nodeMapArray[map_size_rows][map_size_cols], int mapArray[map_size_rows][map_size_cols]);
Node* bfs(Node* nodeMapArray[][map_size_cols], int startPos[2], int destPos[2]);
void dfs_r(Node* nodeMapArray[][map_size_cols], Node* sourceNode, int* listCount, Node* nodePath[]);
void dfs(Node* nodeMapArray[][map_size_cols], int sourcePos[2], int* listCount, Node* nodePath[]);
#endif //UNTITLED2_MAIN_H
