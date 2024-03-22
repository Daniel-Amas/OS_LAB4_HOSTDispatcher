#ifndef QUEUE_H
#define QUEUE_H

#include "process.h"

struct QueueNode {
    struct Process data;
    struct QueueNode *next;
};

typedef struct QueueNode QueueNode;

typedef struct {
    QueueNode *front;
    QueueNode *rear;
} Queue;

void init_queue(Queue *queue);
int is_empty(Queue *queue);
void enqueue(Queue *queue, struct Process process);
struct Process dequeue(Queue *queue);

#endif /* QUEUE_H */
