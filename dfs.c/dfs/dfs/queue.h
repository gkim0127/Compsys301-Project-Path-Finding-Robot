#ifndef QUEUE_H
#define QUEUE_H
#include "node.h"

void initQueue(int* head, int* tail);
void enqueue(Node* queue[], int* tail, Node* element);
Node* dequeue(Node* queue[], int* head);

#endif =
