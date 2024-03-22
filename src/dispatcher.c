#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#   include <windows.h>
#   define SLEEP(msecs) Sleep(msecs)
#elif __unix
#   include <unistd.h>
#   define SLEEP(msecs) sleep(msecs/1000)
#endif

// Process structure
typedef struct Process {
    int arrival_time;
    int priority;
    int cpu_time;
    int memory_size;
    int printers;
    int scanners;
    int modems;
    int cd_drives;
    int remaining_time;
} Process;

// Queue node
typedef struct Node {
    Process *process;
    struct Node *next;
} Node;

// Queue structure
typedef struct Queue {
    Node *front, *rear;
} Queue;

// Initialize queue
void initializeQueue(Queue *q) {
    q->front = q->rear = NULL;
}

// Check if queue is empty
int isEmpty(Queue *q) {
    return q->front == NULL;
}

// Enqueue process
void enqueue(Queue *q, Process *p) {
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->process = p;
    temp->next = NULL;
    if (isEmpty(q))
        q->front = q->rear = temp;
    else {
        q->rear->next = temp;
        q->rear = temp;
    }
}

// Dequeue process
Process *dequeue(Queue *q) {
    if (isEmpty(q))
        return NULL;
    Node *temp = q->front;
    Process *p = temp->process;
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
    return p;
}

// Dispatcher logic
void dispatcherLogic(Queue *realtimeQueue, Queue *userQueue[]) {
    // Check for realtime processes
    if (!isEmpty(realtimeQueue)) {
        Process *rtProcess = dequeue(realtimeQueue);
        printf("Running Real-Time Process:\n");
        printf("Arrival Time: %d, Priority: %d, CPU Time Remaining: %d, Memory Location: %p, Memory Block Size: %d\n",
               rtProcess->arrival_time, rtProcess->priority, rtProcess->remaining_time, rtProcess, rtProcess->memory_size);
        free(rtProcess);
        return;
    }

    // Check for user processes
    for (int i = 0; i < 3; i++) {
        if (!isEmpty(userQueue[i])) {
            Process *userProcess = dequeue(userQueue[i]);
            printf("Running User Process:\n");
            printf("Arrival Time: %d, Priority: %d, CPU Time Remaining: %d, Memory Location: %p, Memory Block Size: %d\n",
                   userProcess->arrival_time, userProcess->priority, userProcess->remaining_time, userProcess, userProcess->memory_size);
            free(userProcess);
            return;
        }
    }

    printf("No processes to run.\n");
}

int main() {
    // Initialize queues
    Queue realtimeQueue, *userQueue[3];
    initializeQueue(&realtimeQueue);
    for (int i = 0; i < 3; i++) {
        userQueue[i] = (Queue *)malloc(sizeof(Queue));
        initializeQueue(userQueue[i]);
    }

    // Open dispatch list file
    char filepath[100];
    printf("Enter the filepath for the dispatch list: ");
    scanf("%s", filepath);

    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Read processes from file and enqueue
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        Process *p = (Process *)malloc(sizeof(Process));
        sscanf(line, "%d, %d, %d, %d, %d, %d, %d, %d",
               &p->arrival_time, &p->priority, &p->cpu_time, &p->memory_size,
               &p->printers, &p->scanners, &p->modems, &p->cd_drives);
        p->remaining_time = p->cpu_time;
        if (p->priority == 0)
            enqueue(&realtimeQueue, p);
        else if (p->priority >= 1 && p->priority <= 3)
            enqueue(userQueue[p->priority - 1], p);
    }

    // Close file
    fclose(file);

    // Run dispatcher logic
    while (!isEmpty(&realtimeQueue) || !isEmpty(userQueue[0]) || !isEmpty(userQueue[1]) || !isEmpty(userQueue[2])) {
        dispatcherLogic(&realtimeQueue, userQueue);
        SLEEP(1000);
    }

    // Free memory
    for (int i = 0; i < 3; i++)
        free(userQueue[i]);

    return 0;
}