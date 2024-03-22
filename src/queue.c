#include <stdlib.h>
#include "queue.h"

void init_queue(Queue *queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

int is_empty(Queue *queue) {
    return queue->front == NULL;
}

void enqueue(Queue *queue, struct Process process) {
    QueueNode *new_node = (QueueNode *)malloc(sizeof(QueueNode));
    if (new_node == NULL) {
        // Handle memory allocation failure
        exit(1);
    }
    new_node->data = process;
    new_node->next = NULL;
    
    if (is_empty(queue)) {
        queue->front = new_node;
        queue->rear = new_node;
    } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
}

struct Process dequeue(Queue *queue) {
    if (is_empty(queue)) {
        // Handle underflow
        exit(1);
    }
    QueueNode *temp = queue->front;
    struct Process data = temp->data;
    queue->front = temp->next;
    free(temp);
    return data;
}
