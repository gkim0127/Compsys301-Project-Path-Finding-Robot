#include "queue.h"

void initQueue(int* head, int* tail)
{
    *head = *tail = 0;
}

void enqueue(Node* queue[], int* tail, Node* element)
{
    queue[(*tail)++] = element;
}

Node* dequeue(Node* queue[], int* head)
{
    return queue[(*head)++];
}